
#ifndef BUTTERFLY_AES_H
#define BUTTERFLY_AES_H

#include "openssl/evp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"

#include "logger.h"

namespace butterfly
{

class CryptoAES
{

private:
    EVP_CIPHER_CTX *_aesEncryptContext, *_aesDecryptContext;

    //unsigned char *_aesKey, *_aesIv;
    //std::string _aesKey, _aesIv;
    int _aesKeyLength, _aesIvLength;

protected:
    unsigned char *_aesKey= (unsigned char *)"01234567890123456789012345678901";
    unsigned char *_aesIv=(unsigned char *)"0123456789012345";

public:
    CryptoAES();
    ~CryptoAES();

    bool generateAESKey();

    size_t encrypt(const unsigned char *message, size_t messageLength, unsigned char **encryptedMessage);
    size_t decrypt(unsigned char *encryptedMessage, size_t encryptedMessageLength, unsigned char **decryptedMessage);

    int readFile(char *filename, unsigned char **file);
    void writeFile(char *filename, unsigned char *file, size_t fileLength);
    char* appendToString(char *string, char *suffix);
};

} // namespace butterfly

#endif //BUTTERFLY_AES_H
