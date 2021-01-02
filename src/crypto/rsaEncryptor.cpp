
#include "crypto/rsaEncryptor.h"

namespace butterfly {

RSAEncryptor::RSAEncryptor() : CryptoRSA() ,_cPrivateRsaKeyFileName("CPrivateRSA.pem"){

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

    //TODO change to fstream
    FILE *out = fopen("key.bin","wb");
    fwrite(ciphertextKey, sizeof(char), static_cast<size_t>(ciphertextLength), out);
}

void RSAEncryptor::generateKeypairFiles() {

    createRSAPrivateKeyFile("CPrivateRSA.pem");

    createPublicKeyFile("CPublic.pem");

}

void RSAEncryptor::saveClientPrivateRSAKeyFile() {

    createRSAPrivateKeyFile(_cPrivateRsaKeyFileName);

}

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
