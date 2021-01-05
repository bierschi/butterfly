
#ifndef BUTTERFLY_RSA_H
#define BUTTERFLY_RSA_H

#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include "logger.h"

#define PADDING RSA_PKCS1_OAEP_PADDING  // length < RSA_SIZE(rsa) - 42 bytes

// Encryption/Decryption block size
// Keysize of 4096
// (4096/8) - 42 = 470 Bytes
// Keysize of 2048
// (2048/8) - 42 = 214 Bytes

namespace butterfly {

/**
 * Class CryptoRSA to provide low level RSA cryptography tasks
 */
class CryptoRSA {

private:
    char *_rsaPrivateKeyStr, *_rsaPublicKeyStr, *_publicKeyStr;
    int _keySize, _paddingSize;

    static RSA *_rsa;

    /**
     * Inits the correct padding size
     */
    void initPaddingSize();

protected:
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
     bool generateRSAKey(); // TODO takes some time to generate the key


public:

    /**
     * Constructor CryptoRSA
     *
     * @param keySize: size of the key
     */
    explicit CryptoRSA(int keySize=4096);

    /**
     * Destructor CryptoRSA
     */
    ~CryptoRSA();

    /**
     * Get the RSA* key
     *
     * @return RSA*
     */
    inline static RSA* getRSAKey() { return CryptoRSA::_rsa; }

    /**
     * Get the RSA size in bytes. RSA key size => (4096/8) = 512
     *
     * @return int: size in bytes
     */
    inline static int getRSAKeySize() { return RSA_size(CryptoRSA::_rsa); }

    /**
     * Get the padding size
     *
     * @return int: padding size
     */
    inline int getPaddingSize() const { return _paddingSize; }

    /**
     * Get the EVP_PKEY from the rsa keypair
     *
     * @return EVP_PKEY
     */
    static EVP_PKEY* getEvpPkey();

    /**
     * Get the EVP_PKEY size
     *
     * @param key: EVP_PKEY
     * @return size as int
     */
    inline static int getEvpPkeySize(EVP_PKEY *key) { return EVP_PKEY_size(key); }

    /**
     * Get the RSA private key string. Starts with -----BEGIN RSA PRIVATE KEY-----
     *
     * @return rsa private key string as char*
     */
    char* getRSAPrivateKey();

    /**
    * Get the RSA public key string. Starts with -----BEGIN RSA PUBLIC KEY-----
    *
    * @return rsa public key string as char*
    */
    char* getRSAPublicKey();

    /**
     * Get the public key string. Starts with -----BEGIN PUBLIC KEY-----
     *
     * @return public key string as char*
     */
    char* getPublicKey();

    /**
     * Creates the RSA private key file. Starts with -----BEGIN RSA PRIVATE KEY-----
     *
     * @param filename: std::string const reference
     *
     * @return boolean, true if creation was successful
     */
    static bool createRSAPrivateKeyFile(const std::string &filename);

    /**
     * Creates the RSA public key file. Starts with -----BEGIN RSA PUBLIC KEY-----
     *
     * @param filename: std::string const reference
     *
     * @return boolean, true if creation was successful
     */
    static bool createRSAPublicKeyFile(const std::string &filename);

    /**
     * Creates the public key file. Starts with -----BEGIN PUBLIC KEY-----
     *
     * @param filename: std::string const reference
     *
     * @return boolean, true if creation was successful
     */
    static bool createPublicKeyFile(const std::string &filename);

    /**
     * Get the EVP_PKEY from RSA private key file
     *
     * @param filepath: path to private key file
     *
     * @return EVP_PKEY from private key file
     */
    static EVP_PKEY* getPkeyFromPrivateKeyFile(const std::string &filepath);

    /**
    * Get the EVP_PKEY from public key file
     *
    * @param filepath: path to public key file
     *
    * @return EVP_PKEY from public key file
    */
    static EVP_PKEY* getPkeyFromPublicKeyFile(const std::string &filepath);

    /**
     * Encrypt the plaintext with the EVP PKEY
     *
     * @param key: EVP_PKEY to encrypt
     * @param plaintext: plaintext to encrypt
     * @param plaintextLength: length of the plaintext
     * @param ciphertext: encrypted ciphertext
     *
     * @return ciphertext length
     */
    static size_t encrypt(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char *ciphertext);

    /**
     * Decrypt the ciphertext with the EVP PKEY
     *
     * @param key: EVP_PKEY to decrypt
     * @param ciphertext: ciphertext to decrypt
     * @param ciphertextLength: length of the ciphertext
     * @param plaintext: decrypted plaintext
     *
     * @return plaintext length
     */
    static size_t decrypt(EVP_PKEY *key, unsigned char* ciphertext, size_t ciphertextLength, unsigned char* plaintext);

};

} // namespace butterfly

#endif //BUTTERFLY_RSA_H
