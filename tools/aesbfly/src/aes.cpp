
#include "aes.h"

namespace tools
{

unsigned char* CryptoAES::aesKey = nullptr;
unsigned char* CryptoAES::aesIv = nullptr;

CryptoAES::CryptoAES()
{
    _aesEncryptContext = EVP_CIPHER_CTX_new();
    _aesDecryptContext = EVP_CIPHER_CTX_new();

    EVP_CIPHER_CTX_init(_aesEncryptContext);
    EVP_CIPHER_CTX_init(_aesDecryptContext);

    EVP_CipherInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, NULL, NULL, 1);

    // Get length from the context
    _aesKeyLength = EVP_CIPHER_CTX_key_length(_aesEncryptContext);
    _aesIvLength = EVP_CIPHER_CTX_iv_length(_aesEncryptContext);

    if (CryptoAES::aesKey == nullptr && CryptoAES::aesIv == nullptr)
    {

        // Allocate correct buffer size
        CryptoAES::aesKey = (unsigned char *) malloc(static_cast<size_t>(_aesKeyLength));
        CryptoAES::aesIv  = (unsigned char *) malloc(static_cast<size_t>(_aesIvLength));

        // Generate the AESKey and AESIV
        if ( !generateAESKeyWithSalt() )
        {
            #ifdef LOGGING
            std::cerr <<"Error on generating an AES Key/IV!" << std::endl;
            #endif
        }
    }

}

CryptoAES::~CryptoAES()
{
    EVP_CIPHER_CTX_reset(_aesEncryptContext);
    EVP_CIPHER_CTX_reset(_aesDecryptContext);
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

bool CryptoAES::initDone()
{
    if ( (CryptoAES::aesKey != nullptr) && (CryptoAES::aesIv != nullptr) )
        return true;
    else
        return false;
}

bool CryptoAES::generateAESKey()
{

    if(RAND_bytes(CryptoAES::aesKey, _aesKeyLength) == 0) {
        return false;
    }

    if(RAND_bytes(CryptoAES::aesIv, _aesIvLength) == 0) {
        return false;
    }

    return true;
}

bool CryptoAES::generateAESKeyWithSalt()
{
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

    if (EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha256(), aesSalt, aesPass, _aesKeyLength, AES_ROUNDS, CryptoAES::aesKey, CryptoAES::aesIv) == 0)
    {
        return false;
    }

    free(aesPass);
    free(aesSalt);

    return true;
}

void CryptoAES::setAESKey(std::string &key)
{

    if (static_cast<int>(key.length()) < _aesKeyLength)
    {
        // fill string to length 32
        key.insert(key.length(), static_cast<unsigned long>(_aesKeyLength), '0');
    }

    CryptoAES::aesKey = reinterpret_cast<unsigned char*>(const_cast<char*>(key.c_str()));

}

void CryptoAES::setAESIv(std::string &iv)
{

    if (static_cast<int>(iv.length()) < _aesIvLength)
    {
        // fill string to length 16
        iv.insert(iv.length(), static_cast<unsigned long>(_aesIvLength), '0');
    }

    CryptoAES::aesIv = reinterpret_cast<unsigned char*>(const_cast<char*>(iv.c_str()));

}

std::string CryptoAES::getAESKey() const
{
    std::string str(reinterpret_cast<const char *>(CryptoAES::aesKey), static_cast<unsigned long>(_aesKeyLength));
    return str;
}

std::string CryptoAES::getAESIv() const
{
    std::string str(reinterpret_cast<const char *>(CryptoAES::aesIv), static_cast<unsigned long>(_aesIvLength));
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

    if (!EVP_EncryptInit_ex(_aesEncryptContext, EVP_aes_256_cbc(), NULL, CryptoAES::aesKey, CryptoAES::aesIv))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_EncryptInit_ex in CryptoAES encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return 0;
    }

    if (!EVP_EncryptUpdate(_aesEncryptContext, *ciphertext, (int *) &blockLength, plaintext,
                           static_cast<int>(plaintextLength)))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_EncryptUpdate in CryptoAES encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return 0;
    }

    ciphertextLength += blockLength;

    if (!EVP_EncryptFinal_ex(_aesEncryptContext, *ciphertext + ciphertextLength, (int *) &blockLength))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_EncryptFinal_ex in CryptoAES encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return 0;
    }

    return ciphertextLength + blockLength;
}

size_t CryptoAES::decrypt(unsigned char *ciphertext, size_t ciphertextLength, unsigned char **plaintext)
{

    size_t plaintextLength = 0;
    size_t blockLength = 0;

    *plaintext = static_cast<unsigned char *>(malloc(ciphertextLength));

    if (!EVP_DecryptInit_ex(_aesDecryptContext, EVP_aes_256_cbc(), NULL, CryptoAES::aesKey, CryptoAES::aesIv))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_DecryptInit_ex in CryptoAES decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return 0;
    }

    if (!EVP_DecryptUpdate(_aesDecryptContext, static_cast<unsigned char *>(*plaintext), (int *) &blockLength,
                           ciphertext, static_cast<int>(ciphertextLength)))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_DecryptUpdate in CryptoAES decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return 0;
    }

    plaintextLength += blockLength;

    if (!EVP_DecryptFinal_ex(_aesDecryptContext, static_cast<unsigned char *>(*plaintext) + plaintextLength,
                             (int *) &blockLength))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_DecryptFinal_ex in CryptoAES decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return 0;
    }

    plaintextLength += blockLength;

    return plaintextLength;
}

} // namespace tools
