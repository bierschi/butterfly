//
// Created on 22.01.20.
//

#include "rsa_algo.h"

RSAAlgorithm::RSAAlgorithm() {



}

RSAAlgorithm::~RSAAlgorithm() {

}

void RSAAlgorithm::createPrivateKey() {

    _privateKey = RSA_generate_key(2048, 3, NULL, NULL);
}

void RSAAlgorithm::encrypt(std::vector<boost::filesystem::path>& files) {
    _files = files;
    for (auto& file: _files) {
        std::cout << file << std::endl;
    }
    //run();
    //join();
}

void RSAAlgorithm::decrypt() {

}

