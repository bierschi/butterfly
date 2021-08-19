
#include "crypto/aes.h"

namespace butterfly
{

CryptoAES::CryptoAES()//: _aesKey(nullptr), _aesIv(nullptr)
{

    _aesEncryptContext = EVP_CIPHER_CTX_new();
    _aesDecryptContext = EVP_CIPHER_CTX_new();

    EVP_CIPHER_CTX_init(_aesEncryptContext);
    EVP_CIPHER_CTX_init(_aesDecryptContext);

    EVP_CipherInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, NULL, NULL, 1);

    _aesKeyLength = EVP_CIPHER_CTX_key_length(_aesEncryptContext);
    _aesIvLength = EVP_CIPHER_CTX_iv_length(_aesEncryptContext);

}

CryptoAES::~CryptoAES()
{
    EVP_CIPHER_CTX_free(_aesEncryptContext);
    EVP_CIPHER_CTX_free(_aesDecryptContext);
}

bool CryptoAES::generateAESKey()
{
    _aesKey = (unsigned char*)malloc(static_cast<size_t>(_aesKeyLength));
    _aesIv = (unsigned char*)malloc(static_cast<size_t>(_aesIvLength));

    if(RAND_bytes(_aesKey, _aesKeyLength) == 0) {
        return false;
    }

    if(RAND_bytes(_aesIv, _aesIvLength) == 0) {
        return false;
    }

    return true;
}

size_t CryptoAES::encrypt(const unsigned char *message, size_t messageLength, unsigned char **encryptedMessage)
{

    if (_aesKey == nullptr || _aesIv == nullptr)
    {
        LOG_ERROR("AESKey or AESIv is not initialized!")
        return -1;
    }

    size_t blockLength = 0;
    size_t encryptedMessageLength = 0;

    *encryptedMessage = static_cast<unsigned char*>(malloc(messageLength + AES_BLOCK_SIZE));

    if(!EVP_EncryptInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, _aesKey, _aesIv)) {
        return -1;
    }

    if(!EVP_EncryptUpdate(_aesEncryptContext, *encryptedMessage, (int*)&blockLength, message, static_cast<int>(messageLength))) {
        return -1;
    }

    encryptedMessageLength += blockLength;

    if(!EVP_EncryptFinal_ex(_aesEncryptContext, *encryptedMessage + encryptedMessageLength, (int*)&blockLength)) {
        return -1;
    }

    return encryptedMessageLength + blockLength;
}

size_t CryptoAES::decrypt(unsigned char *encryptedMessage, size_t encryptedMessageLength, unsigned char **decryptedMessage)
{
    if (_aesKey == nullptr || _aesIv == nullptr)
    {
        LOG_ERROR("ER")
        return -1;
    }

    size_t decryptedMessageLength = 0;
    size_t blockLength = 0;

    *decryptedMessage = (unsigned char*)malloc(encryptedMessageLength);

    if(!EVP_DecryptInit_ex(_aesDecryptContext, EVP_aes_256_cbc(), NULL, _aesKey, _aesIv)) {
        return -1;
    }

    if(!EVP_DecryptUpdate(_aesDecryptContext, (unsigned char*)*decryptedMessage, (int*)&blockLength, encryptedMessage, (int)encryptedMessageLength)) {
        return -1;
    }

    decryptedMessageLength += blockLength;

    if(!EVP_DecryptFinal_ex(_aesDecryptContext, (unsigned char*)*decryptedMessage + decryptedMessageLength, (int*)&blockLength)) {
        return -1;
    }

    decryptedMessageLength += blockLength;

    return decryptedMessageLength;
}


int CryptoAES::readFile(char *filename, unsigned char **file)
{
    FILE *fd = fopen(filename, "rb");
    if(fd == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
        exit(1);
    }

    // Determine size of the file
    fseek(fd, 0, SEEK_END);
    size_t fileLength = static_cast<size_t>(ftell(fd));
    fseek(fd, 0, SEEK_SET);

    // Allocate space for the file
    *file = (unsigned char*)malloc(fileLength);
    if(*file == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }

    // Read the file into the buffer
    size_t bytesRead = fread(*file, 1, fileLength, fd);

    if(bytesRead != fileLength) {
        fprintf(stderr, "Error reading file\n");
        exit(1);
    }

    fclose(fd);

    return static_cast<int>(fileLength);
}


void CryptoAES::writeFile(char *filename, unsigned char *file, size_t fileLength)
{
    FILE *fd = fopen(filename, "wb");
    if(fd == NULL) {
        fprintf(stderr, "Failed to open file: %s\n", strerror(errno));
        exit(1);
    }

    size_t bytesWritten = fwrite(file, 1, fileLength, fd);

    if(bytesWritten != fileLength) {
        fprintf(stderr, "Failed to write file\n");
        exit(1);
    }

    fclose(fd);
}


char* CryptoAES::appendToString(char *string, char *suffix) {
    char *appenedString = (char*)malloc(strlen(string) + strlen(suffix) + 1);

    if(appenedString == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(1);
    }

    sprintf(appenedString, "%s%s", string, suffix);
    return appenedString;
}

} // namespace butterfly