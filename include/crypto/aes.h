
#ifndef BUTTERFLY_AES_H
#define BUTTERFLY_AES_H

#include "openssl/evp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include <openssl/err.h>

#include "logger.h"

#define AES_ROUNDS 6

namespace butterfly
{

namespace aes
{

/**
 * Class CryptoAES to provide low level AES cryptography tasks
 */
class CryptoAES
{

private:
    EVP_CIPHER_CTX *_aesEncryptContext, *_aesDecryptContext;
    int _aesKeyLength, _aesIvLength;

    /**
     * Get the openssl error as a std::string
     *
     * @return std::string: openssl error
     */
    static std::string getOpenSSLError();

protected:
    unsigned char *_aesKey, *_aesIv;
    //unsigned char *_aesKey= (unsigned char *)"01234567890123456789012345678901";
    //unsigned char *_aesIv=(unsigned char *)"0123456789012345";

public:

    /**
     * Constructor CryptoAES
     */
    CryptoAES();

    /**
     * Destructor CryptoAES
     */
    ~CryptoAES();

    /**
     * Generates the AES Key and the AES IV
     *
     * @return True if generation was successful
     */
    bool generateAESKey();

    /**
     * Encrypts the plaintext
     *
     * @param plaintext: plaintext to encrypt
     * @param plaintextLength: length of the plaintext
     * @param ciphertext: encrypted ciphertext
     * @return ciphertext length
     */
    size_t encrypt(const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext);

    /**
     * Decrypts the ciphertext
     *
     * @param ciphertext: ciphertext to decrypt
     * @param ciphertextLength: length of the ciphertext
     * @param plaintext: decrypted plaintext
     * @return plaintext length
     */
    size_t decrypt(unsigned char *ciphertext, size_t ciphertextLength, unsigned char **plaintext);

};

} // namespace aes

} // namespace butterfly

#endif //BUTTERFLY_AES_H
