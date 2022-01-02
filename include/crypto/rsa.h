
#ifndef BUTTERFLY_RSA_H
#define BUTTERFLY_RSA_H

#include <string>

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include "logger.h"
#include "bflyUtils.h"

#define PADDING RSA_PKCS1_OAEP_PADDING

namespace butterfly
{

namespace rsa
{

/**
 * Class CryptoRSA to provide low level RSA cryptography tasks
 */
class CryptoRSA
{

private:
    int _keysize, _paddingSize;
    char *_rsaPrivateKeyStr, *_privateKeyStr, *_publicKeyStr;
    unsigned char* _encryptedKey, *_iv;

    EVP_PKEY *_pkey;
    EVP_CIPHER_CTX *rsaEncryptContext, *rsaDecryptContext;

    /**
     * Get the openssl error as a std::string
     *
     * @return std::string: openssl error
     */
    static std::string getOpenSSLError();

    /**
     * Generates the RSA key
     *
     * @return: boolean, true if generation was successful else false
     */
    bool generateRSAKey();

    /**
    * Loads the rsa key from a file
    *
    * @param filename: std::string to the file path
    * @return boolean: true if key data was successfully loaded from filename, else false
    */
    bool loadKeyFromFile(const std::string &filepath);

    /**
    * Loads the rsa key from a string
    *
    * @param: str: std::string of the key
    * @return boolean: true if key data was successfully loaded from given string, else false
    */
    bool loadKeyFromStr(const std::string &str);

protected:
    /**
    * Get the padding size
    *
    * @return int: padding size
    */
    inline int getPaddingSize() const
    { return _paddingSize; }

public:

    /**
    * Constructor CryptoRSA  to create new rsa key with keySize
    *
    * Usage:
    *      std::unique_ptr<butterfly::rsa::CryptoRSA> _cryptoRSA(new butterfly::rsa::CryptoRSA(2048));
    *      _cryptoRSA->getRSAIV();
    *      _cryptoRSA->getRSAEncryptedKey();
     *
    * @param keySize: size of the key
    */
    explicit CryptoRSA(int keysize);

    /**
    * Constructor CryptoRSA to init rsa key from key string or file
    *
    * Usage:
    *      std::unique_ptr<butterfly::rsa::CryptoRSA> _cryptoRSA(new butterfly::rsa::CryptoRSA(""));
    *      _cryptoRSA->getRSAIV();
    *      _cryptoRSA->getRSAEncryptedKey();
     *
    * @param key: key string or filepath to key
    */
    explicit CryptoRSA(const std::string &key);

    /**
     * Destructor CryptoRSA
     */
    virtual ~CryptoRSA();

    /**
     * Get the RSA IV
     *
     * @return _iv as unsigned char*
     */
    unsigned char* getRSAIV() const;

    /**
     * Get the RSA encrypted Key
     *
     * @return _encryptedKey as unsigned char*
     */
    unsigned char* getRSAEncryptedKey() const;

    /**
     * Get the EVP_PKEY from the rsa keypair
     *
     * @return EVP_PKEY*
     */
    EVP_PKEY *getEvpPkey();

    /**
     * Get the EVP_PKEY size
     *
     * @param key: EVP_PKEY
     * @return size as int
     */
    inline int getEvpPkeySize(EVP_PKEY *key)
    { return EVP_PKEY_size(key); }

    /**
    * Get the RSA private key string. Starts with -----BEGIN RSA PRIVATE KEY-----
    *
    * @return rsa private key string as char*
    */
    char *getRSAPrivateKeyStr();

    /**
    * Get the private key string. Starts with -----BEGIN PRIVATE KEY-----
    *
    * @return private key string as char*
    */
    char *getPrivateKeyStr();

    /**
     * Get the public key string. Starts with -----BEGIN PUBLIC KEY-----
     *
     * @return public key string as char*
     */
    char *getPublicKeyStr();

    /**
    * Encrypt the plaintext with EVP methods
    *
    * @param key: EVP_PKEY to encrypt
    * @param plaintext: plaintext to encrypt
    * @param plaintextLength: length of the plaintext
    * @param ciphertext: encrypted ciphertext
    * @return ciphertext length
    */
    int encryptEVP(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext);

    /**
    * Decrypt the ciphertext with EVP methods
    *
    * @param key: EVP_PKEY to decrypt
    * @param ciphertext: ciphertext to decrypt
    * @param ciphertextLength: length of the ciphertext
    * @param encryptedKey: encrypted rsa key
    * @param iv: iv for rsa encryption
    * @param plaintext: decrypted plaintext
    * @return plaintext length
    */
    int decryptEVP(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *encryptedKey, unsigned char *iv, unsigned char **plaintext);

    /**
    * Encrypt the plaintext with the EVP PKEY
    *
    * @param key: EVP_PKEY to encrypt
    * @param plaintext: plaintext to encrypt
    * @param plaintextLength: length of the plaintext
    * @param ciphertext: encrypted ciphertext
    * @return ciphertext length
    */
    static int encrypt(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char *ciphertext);

    /**
     * Decrypt the ciphertext with the EVP PKEY
     *
     * @param key: EVP_PKEY to decrypt
     * @param ciphertext: ciphertext to decrypt
     * @param ciphertextLength: length of the ciphertext
     * @param plaintext: decrypted plaintext
     * @return plaintext length
     */
    static int decrypt(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *plaintext);
};

} // namespace rsa

} //namespace butterfly

#endif //BUTTERFLY_RSA_H
