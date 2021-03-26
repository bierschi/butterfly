
#include "crypto/rsaEncryptor.h"

namespace butterfly {

RSAEncryptor::RSAEncryptor(int keySize) : CryptoRSA(keySize) {
    LOG_TRACE("Create class RSAEncryptor with key size of " << keySize)
}

RSAEncryptor::RSAEncryptor(const std::string &key) : CryptoRSA(key) {
    LOG_TRACE("Create class RSAEncryptor from rsa key string with key size of " << CryptoRSA::getRSAKeySize() * 8)
}

bool RSAEncryptor::validateStringLengthForRSA(const std::string &msg, const int &keysize) {

    int msgLength = static_cast<int>(msg.length());
    int maxBlockSize = (keysize - CryptoRSA::getPaddingSize());

    if (msgLength < maxBlockSize) {
        LOG_INFO("Message string " << msg << " with length of " << msgLength << " bytes is less than RSA block size of max " << maxBlockSize << " bytes (RSA key size: " << keysize << " - padding size: " << CryptoRSA::getPaddingSize() << ")");
        return true;
    } else {
        LOG_ERROR("Message string " << msg << " with length of " << msgLength << " bytes is greater/equal than RSA block size of max " << maxBlockSize << " bytes (RSA key size: " << keysize << " - padding size: " << CryptoRSA::getPaddingSize() << ")");
        return false;
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

bool RSAEncryptor::encrypt(EVP_PKEY *pkey, const std::string &msg) {

    // first check the message size
    if ( msg.empty() ) {
        LOG_ERROR("Can not encrypt message because it is empty!")
        return false;
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // validate the string length with block size length
    if ( !validateStringLengthForRSA(msg, keysize) ) {
        return false; // TODO exception handling
    }

    unsigned char ciphertextKey[keysize];

    CryptoRSA::encrypt(pkey, (unsigned char*)msg.c_str(), strlen(msg.c_str())+1, ciphertextKey);

    _encryptedKey.resize(static_cast<size_t>(keysize));
    std::copy(ciphertextKey, ciphertextKey + keysize, _encryptedKey.begin());

    return true;
}

} // namespace butterfly
