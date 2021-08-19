
#include "crypto/aes.h"

namespace butterfly
{

namespace aes
{

CryptoAES::CryptoAES() : _aesKey(nullptr), _aesIv(nullptr)
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
    _aesKey = (unsigned char *) malloc(static_cast<size_t>(_aesKeyLength));
    _aesIv = (unsigned char *) malloc(static_cast<size_t>(_aesIvLength));

    auto *aesPass = (unsigned char *) malloc(static_cast<size_t>(_aesKeyLength));
    auto *aesSalt = (unsigned char *) malloc(8);

    if (aesPass == NULL || aesSalt == NULL)
    {
        return false;
    }

    if (RAND_bytes(aesPass, _aesKeyLength) == 0)
    {
        return false;
    }

    if (RAND_bytes(aesSalt, 8) == 0)
    {
        return false;
    }

    if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), aesSalt, aesPass, _aesKeyLength, AES_ROUNDS, _aesKey, _aesIv) ==
        0)
    {
        return false;
    }

    free(aesPass);
    free(aesSalt);

    return true;
}

size_t CryptoAES::encrypt(const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext)
{

    if (_aesKey == nullptr || _aesIv == nullptr)
    {
        LOG_ERROR("AESKey or AESIv is not initialized!")
        return 0;
    }

    size_t blockLength = 0;
    size_t ciphertextLength = 0;

    *ciphertext = static_cast<unsigned char *>(malloc(plaintextLength + AES_BLOCK_SIZE));

    if (!EVP_EncryptInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, _aesKey, _aesIv))
    {
        return 0;
    }

    if (!EVP_EncryptUpdate(_aesEncryptContext, *ciphertext, (int *) &blockLength, plaintext,
                           static_cast<int>(plaintextLength)))
    {
        return 0;
    }

    ciphertextLength += blockLength;

    if (!EVP_EncryptFinal_ex(_aesEncryptContext, *ciphertext + ciphertextLength, (int *) &blockLength))
    {
        return 0;
    }

    return ciphertextLength + blockLength;
}

size_t CryptoAES::decrypt(unsigned char *ciphertext, size_t ciphertextLength, unsigned char **plaintext)
{
    if (_aesKey == nullptr || _aesIv == nullptr)
    {
        LOG_ERROR("AESKey or AESIv is not initialized!")
        return 0;
    }

    size_t plaintextLength = 0;
    size_t blockLength = 0;

    *plaintext = static_cast<unsigned char *>(malloc(ciphertextLength));

    if (!EVP_DecryptInit_ex(_aesDecryptContext, EVP_aes_256_cbc(), NULL, _aesKey, _aesIv))
    {
        return 0;
    }

    if (!EVP_DecryptUpdate(_aesDecryptContext, static_cast<unsigned char *>(*plaintext), (int *) &blockLength,
                           ciphertext, static_cast<int>(ciphertextLength)))
    {
        return 0;
    }

    plaintextLength += blockLength;

    if (!EVP_DecryptFinal_ex(_aesDecryptContext, static_cast<unsigned char *>(*plaintext) + plaintextLength,
                             (int *) &blockLength))
    {
        return 0;
    }

    plaintextLength += blockLength;

    return plaintextLength;
}

} // namespace aes

} // namespace butterfly