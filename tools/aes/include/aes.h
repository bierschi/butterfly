
#ifndef AES_AES_H
#define AES_AES_H

#include <string>
#include <iostream>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#define AES_ROUNDS 6
#define LOGGING

namespace tools
{

class CryptoAES
{

private:
    EVP_CIPHER_CTX *_aesEncryptContext, *_aesDecryptContext;
    int _aesKeyLength, _aesIvLength;

    static std::string getOpenSSLError();

protected:
    static unsigned char *aesKey, *aesIv;

public:

    CryptoAES();
    virtual ~CryptoAES();

    static bool initDone();

    bool generateAESKey();
    bool generateAESKeyWithSalt();

    void setAESKey(std::string &aesKey);
    void setAESIv(std::string &aesIv);
    std::string getAESKey() const;
    std::string getAESIv() const;
    std::string getAESKeyPair() const;
    inline int getAESKeyLength() const { return _aesKeyLength; }
    inline int getAESIVLength() const { return _aesIvLength; }

    size_t encrypt(const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext);
    size_t decrypt(unsigned char *ciphertext, size_t ciphertextLength, unsigned char **plaintext);

};

} // namespace tools

#endif //AES_AES_H
