
#include "crypto/decryptor.h"

namespace butterfly
{

namespace hybrid
{

Decryptor::Decryptor()
{

}

Decryptor::~Decryptor()
{

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

std::string Decryptor::decryptAESKey(const std::string &decryptedCPrivateRSA)
{

    _rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(decryptedCPrivateRSA));

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(AES_KEY_ENC_FILENAME);
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
