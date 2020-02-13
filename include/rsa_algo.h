//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_RSA_ALGO_H
#define RANSOMWARE_RSA_ALGO_H

#include <iostream>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <openssl/rsa.h>
#include <cmath>

#include "crypto.h"

/**
 * Class RSAAlgorithm
 */
class RSAAlgorithm : public Crypto {

private:
    char *_privateKeyStr;
    char *_publicKeyStr;

    static RSA *_keypair;
    static RSA *_privateKey;
    static RSA *_publicKey;

    /**
     * generates the RSA keypairs
     *
     * @return bool true or false
     */
    bool generateKeyPair();

    /**
     * extracts the private and public rsa key from the generated rsa keypair
     *
     * @return bool true or false
     */
    bool extractKeys();

public:

    /**
     * Default Constructor
     */
    RSAAlgorithm();

    /**
     * Constructor with private and public RSA key
     *
     * @param privateKey: RSA*
     * @param publicKey: RSA*
     */
    RSAAlgorithm(RSA* privateKey, RSA* publicKey);

    /**
     * Destructor
     */
    ~RSAAlgorithm();

    char* encrypt(RSA *publicKey, const char *pt);
    char* decrypt(RSA *privateKey, const char *ct);

    std::vector<std::string> messageChunks(const std::string& message);

    /**
     * creates the RSA private key file
     *
     * @param file: bool true or false
     */
    char* createRSAPrivateKeyStr();

    /**
     * creates the RSA public key File
     *
     * @param file: bool true or false
     */
    char* createRSAPublicKeyStr();

    /**
     * creates the RSA private key file
     *
     * @param filename: name of the private key file
     */
    void createRSAPrivateKeyFile(const std::string& filename);

    /**
     * creates the RSA public key file
     *
     * @param filename: name of the public key file
     */
    void createRSAPublicKeyFile(const std::string& filename);

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

    /**
     * get the RSA public key from public key string
     *
     * @param publicKeyStr: string from rsa public key pem file
     * @return RSA*
     */
    RSA* getPublicKeyFromStr(const std::string& publicKeyStr);

    /**
     * get the RSA private key from private key string
     *
     * @param privateKeyStr: string from rsa private key pem file
     * @return RSA*
     */
    RSA* getPrivateKeyFromStr(const std::string& privateKeyStr);

    /**
     * get the private key string
     *
     * @return char*
     */
    char* getPrivateKeyStr();

    /**
     * get the public key string
     *
     * @return char*
     */
    char* getPublicKeyStr();

    /**
     * get the raw rsa private key structure
     *
     * @return RSA*
     */
    RSA* getPrivateKey();

    /**
     * get the raw rsa public key structure
     */
    RSA* getPublicKey();

};


#endif //RANSOMWARE_RSA_ALGO_H
