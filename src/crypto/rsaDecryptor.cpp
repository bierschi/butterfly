
#include "crypto/rsaDecryptor.h"

namespace butterfly {

RSADecryptor::RSADecryptor() : CryptoRSA() {
    LOG_TRACE("Create class RSADecryptor")
}

RSADecryptor::~RSADecryptor() {

}

bool RSADecryptor::decrypt(const std::string &msg) {
    LOG_TRACE("msg: " << msg);
    EVP_PKEY *pkey = CryptoRSA::getPkeyFromPrivateKeyFile("CPrivateRSA.pem");

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    unsigned char buffer[keysize];
    unsigned char plaintextKey[keysize];

    FILE *out = fopen("key.bin", "rb");
    fread(buffer, sizeof(buffer), 1, out);

    LOG_TRACE("Keysize: " << keysize)

    CryptoRSA::decrypt(pkey, buffer, (size_t)keysize, plaintextKey);

    _decryptedKey = reinterpret_cast<char*>(plaintextKey);
    LOG_INFO("Decrypted plaintext key: " << _decryptedKey);

    return true;
}

} // namespace butterfly
