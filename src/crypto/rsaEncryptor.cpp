
#include "crypto/rsaEncryptor.h"

namespace butterfly {

RSAEncryptor::RSAEncryptor(int keySize) : CryptoRSA(keySize) ,_cPrivateRsaKeyFilename("CPrivateRSA.pem"), _cPublicKeyFilename("CPublic.pem"),
                                          _encKeyFilename("key.bin")
{
    LOG_TRACE("Create class RSAEncryptor")
    if (CryptoRSA::getRSAKey() == nullptr) {
        if ( !CryptoRSA::generateRSAKey() ) {
            LOG_ERROR("Could not generate the RSA key!");
            throw std::runtime_error("Could not generate the RSA key!");
        }
    }
}

RSAEncryptor::~RSAEncryptor() {

}

bool RSAEncryptor::validateStringLengthForRSA(const std::string &msg) {

    int msgLength = static_cast<int>(msg.length());
    int maxBlockSize = (CryptoRSA::getRSAKeySize() - CryptoRSA::getPaddingSize());

    if (msgLength < maxBlockSize) {
        LOG_INFO("Message string " << msg << " with length of " << msgLength << " bytes is less than RSA block size of max " << maxBlockSize << " bytes (RSA key size: " << CryptoRSA::getRSAKeySize() << " - padding size: " << CryptoRSA::getPaddingSize() << ")");
        return true;
    } else {
        LOG_ERROR("Message string " << msg << " with length of " << msgLength << " bytes is greater/equal than RSA block size of max " << maxBlockSize << " bytes (RSA key size: " << CryptoRSA::getRSAKeySize() << " - padding size: " << CryptoRSA::getPaddingSize() << ")");
        return false;
    }
}

void RSAEncryptor::saveEncryptedKeyFile(unsigned char *ciphertextKey, int ciphertextLength) {

    std::fstream out(_encKeyFilename, std::ios::out | std::ios::binary);
    if ( out.is_open() ) {
        out.write(reinterpret_cast<char*>(&ciphertextKey[0]), ciphertextLength);
    } else {
        LOG_ERROR("Could not open file " << _encKeyFilename <<" to save the encrypted key");
    }
}

void RSAEncryptor::saveClientPrivateRSAKeyFile() {

    if ( !createRSAPrivateKeyFile(_cPrivateRsaKeyFilename) ) {
        LOG_ERROR("Client private rsa key file could not been saved")
    }

}

void RSAEncryptor::saveClientPublicKeyFile() {

    if ( !createPublicKeyFile(_cPublicKeyFilename) ) {
        LOG_ERROR("Client public key file could not been saved")
    }

}

bool RSAEncryptor::encrypt(const std::string &msg) {

    // first validate the string length with block size length
    if ( !validateStringLengthForRSA(msg) ) {
        return false;
    }

    EVP_PKEY *key = CryptoRSA::getEvpPkey();

    int keysize = CryptoRSA::getEvpPkeySize(key);
    unsigned char ciphertextKey[keysize];

    size_t ciphertextLength = CryptoRSA::encrypt(key, (unsigned char*)msg.c_str(), strlen(msg.c_str())+1, ciphertextKey);

    saveEncryptedKeyFile(ciphertextKey, static_cast<int>(ciphertextLength));

    LOG_TRACE("Ciphertext: " << reinterpret_cast<char*>(ciphertextKey));

    return true;
}

} // namespace butterfly
