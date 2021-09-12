
#include "crypto/aes.h"

namespace butterfly
{

namespace aes
{

CryptoAES::CryptoAES() : _aesKey(nullptr), _aesIv(nullptr)
{

    LOG_TRACE("Create class CryptoAES")
    _aesEncryptContext = EVP_CIPHER_CTX_new();
    _aesDecryptContext = EVP_CIPHER_CTX_new();

    EVP_CIPHER_CTX_init(_aesEncryptContext);
    EVP_CIPHER_CTX_init(_aesDecryptContext);

    EVP_CipherInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, NULL, NULL, 1);

    // Get length from the context
    _aesKeyLength = EVP_CIPHER_CTX_key_length(_aesEncryptContext);
    _aesIvLength = EVP_CIPHER_CTX_iv_length(_aesEncryptContext);

    // Allocate correct buffer size
    _aesKey = (unsigned char *) malloc(static_cast<size_t>(_aesKeyLength));
    _aesIv  = (unsigned char *) malloc(static_cast<size_t>(_aesIvLength));

    // Generate the AESKey and AESIV
    if ( !generateAESKey() )
    {
        LOG_ERROR("Error on generating an AES Key/IV!")
    }
}

CryptoAES::~CryptoAES()
{
    EVP_CIPHER_CTX_free(_aesEncryptContext);
    EVP_CIPHER_CTX_free(_aesDecryptContext);
}

std::string CryptoAES::getOpenSSLError()
{

    char *buf;
    BIO *bio = BIO_new(BIO_s_mem());
    ERR_print_errors(bio);

    size_t len = static_cast<size_t >(BIO_get_mem_data(bio, &buf));
    std::string err(buf, len);
    BIO_free(bio);

    return err;
}

bool CryptoAES::generateAESKey()
{
    LOG_INFO("Create new AES Key and IV pair")

    if(RAND_bytes(_aesKey, _aesKeyLength) == 0) {
        return false;
    }

    if(RAND_bytes(_aesIv, _aesIvLength) == 0) {
        return false;
    }

    return true;
}

bool CryptoAES::generateAESKeyWithSalt()
{
    LOG_INFO("Create new AES Key and IV pair with Salt")

    auto *aesPass = (unsigned char *) malloc(static_cast<size_t>(_aesKeyLength));
    auto *aesSalt = (unsigned char *) malloc(8);

    if (aesPass == nullptr || aesSalt == nullptr)
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

    if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), aesSalt, aesPass, _aesKeyLength, AES_ROUNDS, _aesKey, _aesIv) == 0)
    {
        return false;
    }

    free(aesPass);
    free(aesSalt);

    return true;
}

void CryptoAES::setAESKey(std::string &aesKey)
{

    if (static_cast<int>(aesKey.length()) < _aesKeyLength)
    {
        // fill string to length 32
        aesKey.insert(aesKey.length(), static_cast<unsigned long>(_aesKeyLength), '0');
    }

    _aesKey = reinterpret_cast<unsigned char*>(const_cast<char*>(aesKey.c_str()));

}

void CryptoAES::setAESIv(std::string &aesIv)
{

    if (static_cast<int>(aesIv.length()) < _aesIvLength)
    {
        // fill string to length 16
        aesIv.insert(aesIv.length(), static_cast<unsigned long>(_aesIvLength), '0');
    }

    _aesIv = reinterpret_cast<unsigned char*>(const_cast<char*>(aesIv.c_str()));

}

std::string CryptoAES::getAESKey() const
{
    std::string str(reinterpret_cast<const char *>(_aesKey), static_cast<unsigned long>(_aesKeyLength));
    return str;
}

std::string CryptoAES::getAESIv() const
{
    std::string str(reinterpret_cast<const char *>(_aesIv), static_cast<unsigned long>(_aesIvLength));
    return str;
}

std::string CryptoAES::getAESKeyPair() const
{

    std::string aeskey = getAESKey();
    std::string aesiv = getAESIv();

    aeskey.append(aesiv);

    return aeskey;
}

size_t CryptoAES::encrypt(const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext)
{

    size_t blockLength = 0;
    size_t ciphertextLength = 0;

    *ciphertext = static_cast<unsigned char *>(malloc(plaintextLength + AES_BLOCK_SIZE));

    if (!EVP_EncryptInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, _aesKey, _aesIv))
    {
        LOG_ERROR("Error during EVP_EncryptInit_ex in CryptoAES encrypt: " << getOpenSSLError());
        return 0;
    }

    if (!EVP_EncryptUpdate(_aesEncryptContext, *ciphertext, (int *) &blockLength, plaintext,
                           static_cast<int>(plaintextLength)))
    {
        LOG_ERROR("Error during EVP_EncryptUpdate in CryptoAES encrypt: " << getOpenSSLError());
        return 0;
    }

    ciphertextLength += blockLength;

    if (!EVP_EncryptFinal_ex(_aesEncryptContext, *ciphertext + ciphertextLength, (int *) &blockLength))
    {
        LOG_ERROR("Error during EVP_EncryptFinal_ex in CryptoAES encrypt: " << getOpenSSLError());
        return 0;
    }

    return ciphertextLength + blockLength;
}

size_t CryptoAES::decrypt(unsigned char *ciphertext, size_t ciphertextLength, unsigned char **plaintext)
{

    size_t plaintextLength = 0;
    size_t blockLength = 0;

    *plaintext = static_cast<unsigned char *>(malloc(ciphertextLength));

    if (!EVP_DecryptInit_ex(_aesDecryptContext, EVP_aes_256_cbc(), NULL, _aesKey, _aesIv))
    {
        LOG_ERROR("Error during EVP_DecryptInit_ex in CryptoAES decrypt: " << getOpenSSLError());
        return 0;
    }

    if (!EVP_DecryptUpdate(_aesDecryptContext, static_cast<unsigned char *>(*plaintext), (int *) &blockLength,
                           ciphertext, static_cast<int>(ciphertextLength)))
    {
        LOG_ERROR("Error during EVP_DecryptUpdate in CryptoAES decrypt: " << getOpenSSLError());
        return 0;
    }

    plaintextLength += blockLength;

    if (!EVP_DecryptFinal_ex(_aesDecryptContext, static_cast<unsigned char *>(*plaintext) + plaintextLength,
                             (int *) &blockLength))
    {
        LOG_ERROR("Error during EVP_DecryptFinal_ex in CryptoAES decrypt: " << getOpenSSLError());
        return 0;
    }

    plaintextLength += blockLength;

    return plaintextLength;
}

} // namespace aes

} // namespace butterfly