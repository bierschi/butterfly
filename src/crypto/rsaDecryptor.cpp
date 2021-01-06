
#include "crypto/rsaDecryptor.h"

namespace butterfly {

RSADecryptor::RSADecryptor() : CryptoRSA() {
    LOG_TRACE("Create class RSADecryptor")
}

RSADecryptor::~RSADecryptor() {

}

int RSADecryptor::validateStringLengthForRSA(const std::string &msg, const int &keysize) {
    LOG_TRACE("Validating message length " << msg.length() << " with key size " << keysize);

    if (msg.length() <= 0) {
        return -1;
    } else if (static_cast<int>(msg.length()) > keysize) {
        return -2;
    }
    return 0;
}

EVP_PKEY* RSADecryptor::getEvpPkeyFromFile(const std::string &filepath) {

    EVP_PKEY *pkey = nullptr;
    std::ifstream in(filepath, std::ios::in);

    if ( in.is_open() ) {

        std::string fLine;
        std::getline(in, fLine);

        if (fLine.compare("-----BEGIN RSA PRIVATE KEY-----") == 0) {

            pkey = CryptoRSA::getPkeyFromPrivateKeyFile(filepath);

        } else if (fLine.compare("-----BEGIN PUBLIC KEY-----") == 0) {

            pkey = CryptoRSA::getPkeyFromPublicKeyFile(filepath);

        } else {
            LOG_ERROR("Unsupported file provided with file header: " << fLine);
        }

    } else {
        LOG_ERROR("Failed to open file " << filepath);
    }

    return pkey;
}

std::string RSADecryptor::getBinKeyFileContents(const std::string &filepath) {

    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    std::string encKey;

    if (in.is_open()) {
        encKey = std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        return encKey;
    } else {
        LOG_ERROR("Failed to open file " << filepath);
        return encKey;
    }
}

bool RSADecryptor::decrypt(EVP_PKEY *pkey, const std::string &msg) {

    int keysize = CryptoRSA::getEvpPkeySize(pkey);
    int rc = validateStringLengthForRSA(msg, keysize);
    if ( rc == -1 ) {
        LOG_ERROR("Encrypted message string length is empty!")
        return false;
    } else if (rc == -2 ) {
        LOG_ERROR("Encrypted message string to big for RSA key length!")
        return false;
    }

    unsigned char plaintextKey[keysize];

    CryptoRSA::decrypt(pkey, const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(msg.c_str())), static_cast<size_t >(keysize), plaintextKey);

    _decryptedKey = reinterpret_cast<char*>(plaintextKey);
    LOG_INFO("Decrypted plaintext key: " << _decryptedKey);

    return true;
}

} // namespace butterfly
