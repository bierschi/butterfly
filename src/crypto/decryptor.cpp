
#include "crypto/decryptor.h"

namespace butterfly
{

Decryptor::Decryptor()
{

}

Decryptor::~Decryptor()
{

}

std::string Decryptor::decryptCPrivateRSA(const std::string &keyFromServer)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<RSADecryptor>(new RSADecryptor(keyFromServer));

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->getBinKeyFileContents(CPRIVATERSA_FILENAME);
    EVP_PKEY *cPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    if (_rsaDecryptorCPrivateRSA->decrypt(cPrivateRSAPKey, encCPrivateRSA))
    {
        _decryptedCPrivateRSA = _rsaDecryptorCPrivateRSA->getDecryptedKey();
    }
    LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);
    return _decryptedCPrivateRSA;

}

std::string Decryptor::decryptAESKey(const std::string &decryptedCPrivateRSA)
{

    _rsaDecryptorAESKey = std::unique_ptr<RSADecryptor>(new RSADecryptor(decryptedCPrivateRSA));

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents(AES_KEY_ENC_FILENAME);
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    if (_rsaDecryptorAESKey->decrypt(aesKeyPKey, encAESKey))
    {

        _decryptedAESKey = _rsaDecryptorAESKey->getDecryptedKey();
        LOG_TRACE("Decrypted AES Key: " << _decryptedAESKey);

    } else
    {
        LOG_ERROR("Could not decrypt the AESKey!")
    }

    return _decryptedAESKey;
}

} // namespace butterfly
