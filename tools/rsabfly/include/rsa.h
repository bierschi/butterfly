
#ifndef RSA_RSA_H
#define RSA_RSA_H

#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include "utils.h"

#define PADDING RSA_PKCS1_OAEP_PADDING
//#define LOGGING

namespace tools
{

class CryptoRSA
{

private:
    int _keysize;
    char *_rsaPrivateKeyStr, *_privateKeyStr, *_publicKeyStr;
    unsigned char* _encryptedKey, *_iv;

    EVP_PKEY *_pkey;
    EVP_CIPHER_CTX *rsaEncryptContext, *rsaDecryptContext;

    static std::string getOpenSSLError();

    bool generateRSAKey();

    bool loadKeyFromFile(const std::string &filepath);
    bool loadKeyFromStr(const std::string &str);

public:

    explicit CryptoRSA(int keysize);
    explicit CryptoRSA(const std::string &key);
    virtual ~CryptoRSA();

    inline unsigned char* getRSAIV() const { return _iv; }
    inline unsigned char* getRSAEncryptedKey() const { return _encryptedKey; }
    inline EVP_PKEY *getEvpPkey() { return _pkey; }
    inline int getEvpPkeySize(EVP_PKEY *key) { return EVP_PKEY_size(key); }

    char *getRSAPrivateKeyStr();
    char *getPrivateKeyStr();
    char *getPublicKeyStr();

    int encryptEVP(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext);
    int decryptEVP(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *encryptedKey, unsigned char *iv, unsigned char **plaintext);

    static int encrypt(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char *ciphertext);
    static int decrypt(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *plaintext);

};

} // namespace tools

#endif //RSA_RSA_H
