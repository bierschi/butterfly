
#ifndef BUTTERFLY_AES_H
#define BUTTERFLY_AES_H

#include <string>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
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
    static unsigned char *aesKey, *aesIv;

public:

    /**
     * Constructor CryptoAES
     *
     * Usage:
     *      std::unique_ptr<butterfly::aes::CryptoAES> _cryptoAES(new butterfly::aes::CryptoAES());
     *      _cryptoAES->generateAESKeyWithSalt();
     *      _cryptoAES->getAESKey();
     */
    CryptoAES();

    /**
     * Destructor CryptoAES
     */
    virtual ~CryptoAES();

    /**
     * Check if the init of the AES Key and IV were already done
     *
     * @return True if already initialized, else False
     */
    static bool initDone();

    /**
     * Generates the AES Key and the AES IV
     *
     * @return True if generation was successful
     */
    bool generateAESKey();

    /**
     * Generates the AES Key and the AES IV with a random salt
     *
     * @return True if generation was successful
     */
    bool generateAESKeyWithSalt();

    /**
     * Sets the AESKey
     *
     * @param aesKey: AESKey for the decryption procedure
     */
    void setAESKey(std::string &aesKey);

    /**
     * Sets the AESIv
     *
     * @param aesIv: AESIv for the decryption procedure
     */
    void setAESIv(std::string &aesIv);

    /**
     * Get the AESKey
     *
     * @return AESKey as std::string
     */
    std::string getAESKey() const;

    /**
     * Get the AESIv
     *
     * @return AESIv as std::string
     */
    std::string getAESIv() const;

    /**
     * Get the AESKey and AESIV in one concatenated string
     *
     * @return string with AESKey and AESIV
     */
    std::string getAESKeyPair() const;

    /**
     * Get the AESKEY Length
     *
     * @return Length of the AESKey as an int
     */
    inline int getAESKeyLength() const { return _aesKeyLength; }

    /**
     * Get the AESIV Length
     *
     * @return Length of the AESIV as an int
     */
    inline int getAESIVLength() const { return _aesIvLength; }

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
