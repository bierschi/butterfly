//
// Created on 23.01.20.
//

#include "aes_algo.h"

AESAlgorithm::AESAlgorithm() {

}

AESAlgorithm::~AESAlgorithm() {

}

int AESAlgorithm::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {

    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    if (!(ctx = EVP_CIPHER_CTX_new())){
        ERR_print_errors_fp(stderr);
    }

    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        ERR_print_errors_fp(stderr);
    }
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        ERR_print_errors_fp(stderr);
    }

    ciphertext_len = len;
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        ERR_print_errors_fp(stderr);
    }

    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int AESAlgorithm::decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {

    EVP_CIPHER_CTX * ctx;

    int len;
    int plaintext_len;

    if (!(ctx=EVP_CIPHER_CTX_new())) {
        ERR_print_errors_fp(stderr);
    }
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv)) {
        ERR_print_errors_fp(stderr);
    }

    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        ERR_print_errors_fp(stderr);
    }
    plaintext_len = len;

    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        ERR_print_errors_fp(stderr);
    }
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
    return plaintext_len;
}

void AESAlgorithm::start() {

    unsigned char *key = (unsigned char *) "01234567890123456789012345678901";
    unsigned char *iv = (unsigned char *) "0123456789012345";

    unsigned char *plaintext = (unsigned char *) "The quick brown fox jumps over the lazy dog";

    unsigned char ciphertext[128];
    unsigned  char decryptedtext[128];

    int decryptedtext_len, ciphertext_len;

    ciphertext_len = encrypt(plaintext, strlen((char *)plaintext), key, iv, ciphertext);
    printf("Ciphertext is: \n");
    BIO_dump_fp(stdout, (const char*)ciphertext, ciphertext_len);

    decryptedtext_len = decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    decryptedtext[decryptedtext_len] = '\0';
    printf("Decrypted text is: \n");
    printf("%s\n", decryptedtext);
}
