//
// Created on 23.01.20.
//

#ifndef RANSOMWARE_AES_ALGO_H
#define RANSOMWARE_AES_ALGO_H

#include <openssl/aes.h>

#include "crypto.h"

class AESAlgorithm : public Crypto {

public:
    AESAlgorithm();
    ~AESAlgorithm();

    void encrypt();
    void decrypt();

};


#endif //RANSOMWARE_AES_ALGO_H
