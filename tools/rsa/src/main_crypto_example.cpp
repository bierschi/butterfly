#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cmath>
#include <cstring>
#include <cstdio>
#include "rsa_crypto_example.h"
#include "utils.h"

std::string getMessage(const char *prompt);

char* base64Encode(const unsigned char *message, const size_t length) {
    int encodedSize = 4 * std::ceil((double)length / 3);
    char *b64text = (char*)malloc(encodedSize + 1);

    if(b64text == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    BIO_write(bio, message, length);
    BIO_flush(bio);

    BUF_MEM *bufferPtr;
    BIO_get_mem_ptr(bio, &bufferPtr);
    BIO_set_close(bio, BIO_CLOSE);

    memcpy(b64text, (*bufferPtr).data, (*bufferPtr).length + 1);
    b64text[(*bufferPtr).length] = '\0';

    BIO_free_all(bio);
    return b64text;
}

void encryptRsa(Crypto *crypto) {
    // Get the message to encrypt
    //std::string message = getMessage("Message to RSA encrypt: ");
    std::string message = "abcdef";
    // Encrypt the message with RSA
    // +1 on the string length argument because we want to encrypt the NUL terminator too
    unsigned char *encryptedMessage = NULL;
    unsigned char *encryptedKey;
    unsigned char *iv;
    size_t encryptedKeyLength;
    size_t ivLength;

    int encryptedMessageLength = crypto->rsaEncrypt((const unsigned char*)message.c_str(), message.size()+1,
                                                    &encryptedMessage, &encryptedKey, &encryptedKeyLength, &iv, &ivLength);

    if(encryptedMessageLength == -1) {
        fprintf(stderr, "Encryption failed\n");
        return;
    }
    writeBinFile("enc.bin", reinterpret_cast<const char *>(encryptedMessage), encryptedMessageLength);

    // Print the encrypted message as a base64 string
    char* b64Message = base64Encode(encryptedMessage, encryptedMessageLength);
    printf("Encrypted message: %s\n", b64Message);

    // Decrypt the message
    char *decryptedMessage = NULL;

    int decryptedMessageLength = crypto->rsaDecrypt(encryptedMessage, (size_t)encryptedMessageLength,
                                                    encryptedKey, encryptedKeyLength, iv, ivLength, (unsigned char**)&decryptedMessage);

    if(decryptedMessageLength == -1) {
        fprintf(stderr, "Decryption failed\n");
        return;
    }

    printf("Decrypted message: %s\n", decryptedMessage);

    // Clean up
    free(encryptedMessage);
    free(decryptedMessage);
    free(encryptedKey);
    free(iv);
    free(b64Message);

    encryptedMessage = NULL;
    decryptedMessage = NULL;
    encryptedKey = NULL;
    iv = NULL;
    b64Message = NULL;
}

std::string getMessage(const char *prompt) {
    std::string message;

    printf(prompt);
    fflush(stdout);

    getline(std::cin, message);
    return message;
}

void printKeys(Crypto *crypto) {

    FILE *f1, *f2, *f3;
    f1 = fopen("private_key.pem", "w");
    f2 = fopen("public_key.pem", "w");
    //f3 = fopen("f3.pem", "w");
    crypto->writeKeyToFile(f1, KEY_SERVER_PRI);
    crypto->writeKeyToFile(f2, KEY_SERVER_PUB);
    //crypto->writeKeyToFile(f3, KEY_CLIENT_PUB);

    fclose(f1);
    fclose(f2);
    //fclose(f3);
}

void printBytesAsHex(unsigned char *bytes, size_t length, const char *message) {
    printf("%s: ", message);

    for(unsigned int i=0; i<length; i++) {
        printf("%02hhx", bytes[i]);
    }

    puts("");
}

int main(int argc, char **argv)
{
    Crypto crypto;

    printKeys(&crypto);

    encryptRsa(&crypto);
    /*
    while(!std::cin.eof()) {
        encryptRsa(&crypto);
    }*/

    return 0;
}
