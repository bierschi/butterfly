
#include "crypto/encryptor.h"

namespace butterfly {

Encryptor::Encryptor() : _rsaEncryptorAESKey(new RSAEncryptor(2048)),
                         _rsaEncryptorCPrivateRSA(new RSAEncryptor(SPUBLIC_PEM)) {

}

Encryptor::~Encryptor() {

}

void Encryptor::encryptAESKey() {

    if ( _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), _aesKey) ) {
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedKey();
        _rsaEncryptorAESKey->saveEncryptedKeyFile("AESKey.bin", aesKeyEnc, _rsaEncryptorAESKey->getRSAKeySize());
    } else {
        LOG_ERROR("Could not encrypt the AES key!");
    }
}

void Encryptor::encryptCPrivateRSA() {

    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();
    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    if (_rsaEncryptorCPrivateRSA->encrypt(cPrivateRSAPKey, cPrivateRSAStr.substr(0, cPrivateRSAStr.size()-1)) ) {
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedKey();
        _rsaEncryptorCPrivateRSA->saveEncryptedKeyFile("CPrivateRSA.bin", cPrivateRSAEnc, _rsaEncryptorCPrivateRSA->getEvpPkeySize(cPrivateRSAPKey));
    } else {
        LOG_ERROR("Could not encrypt the cPrivateRSA key");
    }
}

} // namespace butterfly
