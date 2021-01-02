
#ifndef BUTTERFLY_RSA_H
#define BUTTERFLY_RSA_H

#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include "logger.h"

#define KEYSIZE 4096
#define PADDING RSA_PKCS1_OAEP_PADDING

namespace butterfly {

/**
 * Class CryptoRSA to provide basic RSA cryptography tasks
 */
class CryptoRSA {

private:
    static RSA *_rsa;
    char *_rsaPrivateKeyStr, *_rsaPublicKeyStr, *_publicKeyStr;

protected:
    /**
     * Generates the RSA key
     *
     * @return: boolean, true if generation was successful else false
     */
    static bool generateRSAKey(); // TODO takes some time to generate the key

public:

    /**
     * Constructor CryptoRSA
     */
    CryptoRSA();

    /**
     * Destructor CryptoRSA
     */
    ~CryptoRSA();

    static RSA* getRSAKey();

    /**
     * Get the EVP_PKEY from the rsa keypair
     *
     * @return EVP_PKEY
     */
    static EVP_PKEY* getEvpPkey();

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
     */
    static void createRSAPrivateKeyFile(const std::string &filename);

    /**
     * Creates the RSA public key file. Starts with -----BEGIN RSA PUBLIC KEY-----
     *
     * @param filename: std::string const reference
     */
    static void createRSAPublicKeyFile(const std::string &filename);

    /**
     * Creates the public key file. Starts with -----BEGIN PUBLIC KEY-----
     *
     * @param filename: std::string const reference
     */
    static void createPublicKeyFile(const std::string &filename);

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
     * @param key: EVP_PKEY
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
     * @param key: EVP_PKEY
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
