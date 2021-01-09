
#include "crypto/rsaEncryptor.h"

namespace butterfly {

RSAEncryptor::RSAEncryptor(int keySize) : CryptoRSA(keySize) ,_cPrivateRsaKeyFilename("CPrivateRSA.pem"), _cPublicKeyFilename("CPublic.pem")
{
    LOG_TRACE("Create class RSAEncryptor")

}

RSAEncryptor::RSAEncryptor(const std::string &key) : CryptoRSA(key) {
    LOG_TRACE("Create class RSAEncryptor")
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

void RSAEncryptor::saveEncryptedKeyFile(const std::string &filename, unsigned char *ciphertextKey, int ciphertextLength) {

    std::fstream out(filename, std::ios::out | std::ios::binary);
    if ( out.is_open() ) {
        out.write(reinterpret_cast<char*>(&ciphertextKey[0]), ciphertextLength);
    } else {
        LOG_ERROR("Could not open file " << filename <<" to save the encrypted key");
    }
}

void RSAEncryptor::saveEncryptedKeyFile(const std::string &filename, const std::string &ciphertextKey, int keyLength) {

    std::fstream out(filename, std::ios::out | std::ios::binary);
    if ( out.is_open() ) {
        out.write(ciphertextKey.c_str(), keyLength);
    } else {
        LOG_ERROR("Could not open file " << filename <<" to save the encrypted key");
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

bool RSAEncryptor::encrypt(EVP_PKEY *pkey, const std::string &msg) {

    // first check message size
    if ( msg.empty() ) {
        return false;
    }
    // validate the string length with block size length

    if ( !validateStringLengthForRSA(msg) ) {
        return false; // TODO exception handling
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);
    LOG_TRACE("KEYSIZE: " << keysize)
    unsigned char ciphertextKey[keysize];

    CryptoRSA::encrypt(pkey, (unsigned char*)msg.c_str(), strlen(msg.c_str())+1, ciphertextKey);

    _encryptedKey.resize(static_cast<size_t >(keysize));
    std::copy(ciphertextKey, ciphertextKey + keysize, _encryptedKey.begin());

    LOG_TRACE("Ciphertext: " << _encryptedKey);

    return true;
}

} // namespace butterfly
