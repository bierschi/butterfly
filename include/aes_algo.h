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

    void start();
    int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);
    int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);

};


#endif //RANSOMWARE_AES_ALGO_H
