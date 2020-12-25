//
// Created on 23.01.20.
//

#include <iostream>
#include <fstream>
#include "../include/aes_algo.h"

#define BYTES_PER_GROUP 4
#define GROUPS_PER_LINE 4
#define BYTES_PER_LINE (BYTES_PER_GROUP * GROUPS_PER_LINE)

AESAlgorithm::AESAlgorithm(int initRounds) : _initRounds(initRounds){
    // create encrypt/decrypt context
    _encCTX = EVP_CIPHER_CTX_new();
    _decCTX = EVP_CIPHER_CTX_new();
    // generates random bytes
    RAND_bytes(&_key[0], 32);
    RAND_bytes(&_iv[0], 32);
}

AESAlgorithm::~AESAlgorithm() {
    EVP_CIPHER_CTX_cleanup(_encCTX);
    EVP_CIPHER_CTX_cleanup(_decCTX);
}


void AESAlgorithm::print_hex(unsigned char *str, int len) {
    unsigned long i, j, preflen = 0;

    for (i = 0;  i < len;  i++) {
        printf("%02X ", str[i]);
        if (((i % BYTES_PER_LINE) == (BYTES_PER_LINE - 1)) && ((i + 1) != len)) {
            putchar('\n');
            for (j = 0;  j < preflen;  j++) putchar(' ');
        }
        else if ((i % BYTES_PER_GROUP) == (BYTES_PER_GROUP - 1)) putchar(' ');
    }
    putchar('\n');
}
void AESAlgorithm::init(unsigned char *keyData, unsigned char *salt) {

    int keyDataLen = strlen((const char*) keyData);
    int i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), salt, keyData, keyDataLen, _initRounds, _key, _iv);

    if ( i != 32) {
        std::cerr << "Wrong Key size of: " << i << std::endl;
    }

    EVP_CIPHER_CTX_init(_encCTX);
    EVP_EncryptInit_ex(_encCTX, EVP_aes_256_cbc(), NULL, _key, _iv);
    EVP_CIPHER_CTX_init(_decCTX);
    EVP_DecryptInit_ex(_decCTX, EVP_aes_256_cbc(), NULL, _key, _iv);

}

unsigned char* AESAlgorithm::getKey() {
    return _key;
}

int AESAlgorithm::encrypt(unsigned char *plaintext, int plaintextLen, unsigned char *ciphertext) {

    int fLen;
    //int plaintextLen = strlen((const char*)plaintext) + 1;
    //int ciphertextLen = strlen((const char*)plaintext) + AES_BLOCK_SIZE;
    int ciphertext_len;

    //unsigned char *ciphertext = static_cast<unsigned char *>(malloc(ciphertextLen));

    if(1 != EVP_EncryptInit_ex(_encCTX, NULL, NULL, NULL, NULL)) {
        ERR_print_errors_fp(stderr);
    }

    if (1 != EVP_EncryptUpdate(_encCTX, ciphertext, &fLen, plaintext, plaintextLen)) {
        ERR_print_errors_fp(stderr);
    }
    ciphertext_len = fLen;
    if (1 != EVP_EncryptFinal_ex(_encCTX, ciphertext + fLen, &fLen)) {
        ERR_print_errors_fp(stderr);
    }

    //*plaintextLen = ciphertextLen + fLen;
    ciphertext_len += fLen;
    std::cout << " flen: " << fLen << std::endl;
    return ciphertext_len;
}

int AESAlgorithm::decrypt(unsigned char *ciphertext, int ciphertextLen, unsigned char *plaintext) {

    int len;
    int plaintext_len;
    //int plaintextLen = *ciphertextLen, fLen = 0;
    //unsigned char *plaintext = static_cast<unsigned char *>(malloc(plaintextLen));

    if (1 != EVP_DecryptInit_ex(_decCTX, NULL, NULL, NULL, NULL)) {
        ERR_print_errors_fp(stderr);
    }
    
    if (1 != EVP_DecryptUpdate(_decCTX, plaintext, &len, ciphertext, ciphertextLen)) {
        ERR_print_errors_fp(stderr);
    }
    plaintext_len = len;
    if (1 != EVP_DecryptFinal_ex(_decCTX, plaintext + len, &len)) {
        ERR_print_errors_fp(stderr);
    }
    plaintext_len += len;
    //*ciphertextLen = plaintextLen + fLen;
    std::cout << "flen: " << len << std::endl;
    return plaintext_len;
}


void AESAlgorithm::start() {


    unsigned char *plaintext = (unsigned char *) "The quick brown fox jumps over the lazy dog"
                                                 "The quick brown fox jumps over the lazy dog";

    unsigned char ciphertext[128];
    unsigned  char decryptedtext[128];


    unsigned int salt[] = {12345, 54321};
    unsigned char *keyData = (unsigned char *) "0123456789ABCDEF";


    init(keyData, (unsigned char*)(&salt));
    print_hex(getKey(), sizeof(getKey()));
    // encrypt

    int plaintextLen = strlen(reinterpret_cast<const char *>(plaintext)) + 1;
    int ciphertext_len  = encrypt(plaintext, plaintextLen, ciphertext);

    std::ofstream outputfile("test.txt", std::ios_base::binary);
    outputfile << ciphertext;
    outputfile.close();


    // decrpyt
    std::ifstream inputfile("test.txt", std::ios_base::binary);
   //std::string ciphertext;
    inputfile >> ciphertext;
    //int ciphertext_len = ciphertext.length();
    std::cout << "ciphertext: " << ciphertext_len << std::endl;
    int decryptedtext_len = decrypt(ciphertext, ciphertext_len, decryptedtext);

    std::cout << "decrpyted text: " << decryptedtext << std::endl;


}
