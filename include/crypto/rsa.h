
#ifndef BUTTERFLY_RSA_H
#define BUTTERFLY_RSA_H

#include <string>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#include "logger.h"

#define KEYSIZE 4096

namespace butterfly {

/**
 * Class CryptoRSA to provide basic RSA cryptography tasks
 */
class CryptoRSA {

private:
    static RSA *_rsa;
    char *_rsaPrivateKeyStr, *_rsaPublicKeyStr, *_publicKeyStr;

    /**
     * Generates the RSA key
     *
     * @return: boolean, true if generation was successful else false
     */
    bool generateRSAKey();
public:
    /**
     * Get the RSA public key string. Starts with -----BEGIN RSA PUBLIC KEY-----
     *
     * @return rsa public key string as char*
     */
    char* getRSAPublicKey();

    /**
     * Creates the RSA public key file. Starts with -----BEGIN RSA PUBLIC KEY-----
     *
     * @param filename: std::string const reference
     */
    void createRSAPublicKeyFile(const std::string &filename);


    /**
     * Constructor CryptoRSA
     */
    CryptoRSA();

    /**
     * Destructor CryptoRSA
     */
    ~CryptoRSA();

    /**
     * Get the RSA private key string. Starts with -----BEGIN RSA PRIVATE KEY-----
     *
     * @return rsa private key string as char*
     */
    char* getRSAPrivateKey();

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
    void createRSAPrivateKeyFile(const std::string &filename);

    /**
     * Creates the public key file. Starts with -----BEGIN PUBLIC KEY-----
     *
     * @param filename: std::string const reference
     */
    void createPublicKeyFile(const std::string &filename);


    /**
    *
    * @param filepath: path to pem file
    * @return RSA*
    */
    RSA* getPublicKeyFromFile(const std::string& filepath);

    /**
     * get the RSA private key from pem file
     *
     * @param filepath: path to pem file
     * @return RSA*
     */
    RSA* getPrivateKeyFromFile(const std::string& filepath);


    char* encrypt(RSA *publicKey, const char *plaintext);
    char* decrypt(RSA *privateKey, const char *ciphertext);
};

} // namespace butterfly
#endif //BUTTERFLY_RSA_H
