
#include "crypto/rsaEncryptor.h"

namespace butterfly {

RSAEncryptor::RSAEncryptor() : CryptoRSA() ,_cPrivateRsaKeyFilename("CPrivateRSA.pem"), _encryptedKeyFilename("key.bin"){

    if (getRSAKey() == nullptr) {
        if ( !generateRSAKey() ) {
            LOG_ERROR("Could not generate the RSA key!");
            throw std::runtime_error("Could not generate the RSA key!");
        }
    }
}

RSAEncryptor::~RSAEncryptor() {

}

void RSAEncryptor::saveEncryptedKeyFile(unsigned char *ciphertextKey, int ciphertextLength) {

    std::fstream out(_encryptedKeyFilename, std::ios::out | std::ios::binary);
    if ( out.is_open() ) {
        out.write(reinterpret_cast<char*>(&ciphertextKey[0]), ciphertextLength);
    } else {
        LOG_ERROR("Could not open file " << _encryptedKeyFilename <<" to save the encrypted key");
    }
}

void RSAEncryptor::saveClientPrivateRSAKeyFile() {

    if ( !createRSAPrivateKeyFile(_cPrivateRsaKeyFilename) ) {
        LOG_ERROR("Client private rsa key file could not been saved")
    }

}
// TODO check size of std::string and make message chunks for encryption
void RSAEncryptor::encrypt(const std::string &key) {
    LOG_TRACE("Encrypting the plaintext key: " << key);

    const char *plaintextKey = key.c_str();

    //EVP_PKEY *pkey = CryptoRSA::getPkeyFromPublicKeyFile("CPublic.pem");
    EVP_PKEY *pkey = CryptoRSA::getEvpPkey();

    int keysize = EVP_PKEY_size(pkey);
    LOG_TRACE("Encrypting with keysize of: " << keysize);
    unsigned char ciphertextKey[keysize];

    size_t ciphertextLength = CryptoRSA::encrypt(pkey, (unsigned char*)plaintextKey, strlen(plaintextKey)+1, ciphertextKey);

    saveEncryptedKeyFile(ciphertextKey, static_cast<int>(ciphertextLength));
    LOG_TRACE("Ciphertext: " << reinterpret_cast<char*>(ciphertextKey));

}

} // namespace butterfly
