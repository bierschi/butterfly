
#include "crypto/rsa.h"

namespace butterfly
{

namespace rsa
{

CryptoRSA::CryptoRSA(int keysize) :  _keysize(keysize), _pkey(nullptr)
{
    // Initalize contexts
    rsaEncryptContext = EVP_CIPHER_CTX_new();
    rsaDecryptContext = EVP_CIPHER_CTX_new();

    if (PADDING == RSA_PKCS1_OAEP_PADDING)
    {
        _paddingSize = 42;
    }

    // Generate the RSA Key
    if ( !generateRSAKey() )
    {
        LOG_ERROR("Error at generating the RSA key!");
        throw std::runtime_error("Error at generating the RSA key!");
    }
}

CryptoRSA::CryptoRSA(const std::string &key) : _keysize(-1), _pkey(nullptr)
{
    // Initalize contexts
    rsaEncryptContext = EVP_CIPHER_CTX_new();
    rsaDecryptContext = EVP_CIPHER_CTX_new();

    if (PADDING == RSA_PKCS1_OAEP_PADDING)
    {
        _paddingSize = 42;
    }

    // Load pkey from file or string
    if ( !loadKeyFromFile(key) )
    {
        LOG_ERROR("Could not load key from file/string!");
    }

}

CryptoRSA::~CryptoRSA()
{
    EVP_PKEY_free(_pkey);

    EVP_CIPHER_CTX_free(rsaEncryptContext);
    EVP_CIPHER_CTX_free(rsaDecryptContext);
}

std::string CryptoRSA::getOpenSSLError()
{
    char *buf;
    BIO *bio = BIO_new(BIO_s_mem());
    ERR_print_errors(bio);

    size_t len = static_cast<size_t >(BIO_get_mem_data(bio, &buf));
    std::string err(buf, len);
    BIO_free(bio);

    return err;
}

bool CryptoRSA::generateRSAKey()
{

    EVP_PKEY_CTX *context = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

    if(EVP_PKEY_keygen_init(context) <= 0)
    {
        return false;
    }

    if(EVP_PKEY_CTX_set_rsa_keygen_bits(context, _keysize) <= 0)
    {
        return false;
    }

    if(EVP_PKEY_keygen(context, &_pkey) <= 0)
    {
        return false;
    }

    EVP_PKEY_CTX_free(context);

    return true;
}

bool CryptoRSA::loadKeyFromFile(const std::string &filepath)
{

    if ( butterfly::existsFile(filepath) )
    {
        if ( loadKeyFromStr(butterfly::readBinFile(filepath)) )
        {
            LOG_TRACE("Loaded successfully rsa key from file " << filepath);
            return true;
        }
    } else
    {
        if ( loadKeyFromStr(filepath) )
        {
            LOG_TRACE("Loaded successfully rsa key from string!")
            return true;
        }
    }

    return false;
}

bool CryptoRSA::loadKeyFromStr(const std::string &str)
{

    std::string fLine;
    std::istringstream f(str);
    std::getline(f, fLine);

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    BIO_write(bioPrivate, str.c_str(), static_cast<int>(str.length()));

    if (fLine == "-----BEGIN RSA PRIVATE KEY-----")
    {

        _pkey = PEM_read_bio_PrivateKey(bioPrivate, nullptr, nullptr, nullptr);


    } else if (fLine == "-----BEGIN PUBLIC KEY-----")
    {

        _pkey = PEM_read_bio_PUBKEY(bioPrivate, nullptr, nullptr, nullptr);

    } else
    {
        LOG_ERROR("Unsupported file provided with file header: " << fLine);
        BIO_free(bioPrivate);
        return false;
    }

    BIO_free(bioPrivate);

    return true;
}

unsigned char* CryptoRSA::getRSAIV() const
{
    return _iv;
}

unsigned char* CryptoRSA::getRSAEncryptedKey() const
{
    return _encryptedKey;
}

EVP_PKEY* CryptoRSA::getEvpPkey()
{
    return _pkey;
}

char* CryptoRSA::getRSAPrivateKeyStr()
{
    RSA *rsaPrivateKey = EVP_PKEY_get0_RSA(_pkey);

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bioPrivate, rsaPrivateKey, nullptr, nullptr, 0, nullptr, nullptr);

    BIO_flush(bioPrivate);
    BIO_get_mem_data(bioPrivate, &_rsaPrivateKeyStr);

    return _rsaPrivateKeyStr;
}

char* CryptoRSA::getPrivateKeyStr()
{

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_PrivateKey(bioPrivate, _pkey, NULL, NULL, 0, 0, NULL);

    BIO_flush(bioPrivate);
    BIO_get_mem_data(bioPrivate, &_privateKeyStr);

    return _privateKeyStr;
}

char* CryptoRSA::getPublicKeyStr()
{

    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bioPublic, _pkey);

    BIO_flush(bioPublic);
    BIO_get_mem_data(bioPublic, &_publicKeyStr);

    return _publicKeyStr;
}

size_t CryptoRSA::encryptEVP(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char **ciphertext)
{

    size_t encryptedMessageLength = 0;
    size_t blockLength = 0;
    size_t encryptedKeyLength;

    _encryptedKey = (unsigned char*)malloc(static_cast<size_t>(EVP_PKEY_size(key)));
    _iv = (unsigned char*)malloc(EVP_MAX_IV_LENGTH);

    *ciphertext = (unsigned char*)malloc(plaintextLength + EVP_MAX_IV_LENGTH);

    if(!EVP_SealInit(rsaEncryptContext, EVP_aes_256_cbc(), &_encryptedKey, (int*)&encryptedKeyLength, _iv, &key, 1))
    {
        LOG_ERROR("Error during EVP_SealInit in RSA encrypt: " << getOpenSSLError());
        return 0;
    }


    if(!EVP_SealUpdate(rsaEncryptContext, *ciphertext + encryptedMessageLength, (int*)&blockLength, (const unsigned char*)plaintext, (int)plaintextLength))
    {
        LOG_ERROR("Error during EVP_SealUpdate in RSA encrypt: " << getOpenSSLError());
        return 0;
    }
    encryptedMessageLength += blockLength;

    if(!EVP_SealFinal(rsaEncryptContext, *ciphertext + encryptedMessageLength, (int*)&blockLength))
    {
        LOG_ERROR("Error during EVP_SealFinal in RSA encrypt: " << getOpenSSLError());
        return 0;
    }
    encryptedMessageLength += blockLength;

    return encryptedMessageLength;
}

size_t CryptoRSA::decryptEVP(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *encryptedKey, unsigned char *iv, unsigned char **plaintext)
{

    size_t decryptedMessageLength = 0;
    size_t blockLength = 0;

    *plaintext = (unsigned char*)malloc(ciphertextLength + EVP_MAX_IV_LENGTH);

    if(!EVP_OpenInit(rsaDecryptContext, EVP_aes_256_cbc(), encryptedKey, getEvpPkeySize(key), iv, key))
    {
        LOG_ERROR("Error during EVP_OpenInit in RSA decrypt: " << getOpenSSLError());
        return 0;
    }

    if(!EVP_OpenUpdate(rsaDecryptContext, (unsigned char*)*plaintext + decryptedMessageLength, (int*)&blockLength, ciphertext, (int)ciphertextLength))
    {
        LOG_ERROR("Error during EVP_OpenUpdate in RSA decrypt: " << getOpenSSLError());
        return 0;
    }
    decryptedMessageLength += blockLength;

    if(!EVP_OpenFinal(rsaDecryptContext, (unsigned char*)*plaintext + decryptedMessageLength, (int*)&blockLength))
    {
        LOG_ERROR("Error during EVP_OpenFinal in RSA decrypt: " << getOpenSSLError());
        return 0;
    }
    decryptedMessageLength += blockLength;

    return decryptedMessageLength;
}

size_t CryptoRSA::encrypt(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char *ciphertext)
{

    EVP_PKEY_CTX *ctx;
    size_t ciphertextLength;
    ctx = EVP_PKEY_CTX_new(key, nullptr);

    if (!ctx)
    {
        LOG_ERROR("Error during context init in RSA encrypt: " << getOpenSSLError());
        return 0;
    }
    if (EVP_PKEY_encrypt_init(ctx) <= 0)
    {
        LOG_ERROR("Error during EVP_PKEY_encrypt_init(ctx) in RSA encrypt: " << getOpenSSLError());
        return 0;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx, PADDING) <= 0)
    {
        LOG_ERROR("Error during EVP_PKEY_CTX_set_rsa_padding in RSA encrypt: " << getOpenSSLError());
        return 0;
    }
    if (EVP_PKEY_encrypt(ctx, ciphertext, &ciphertextLength, plaintext, plaintextLength) <= 0)
    {

        LOG_ERROR("Error during EVP_PKEY_encrypt in RSA encrypt: " << getOpenSSLError());
        return 0;
    }

    return ciphertextLength;

}

size_t CryptoRSA::decrypt(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *plaintext)
{

    EVP_PKEY_CTX *ctx;
    size_t plaintextLength;
    ctx = EVP_PKEY_CTX_new(key, nullptr);

    if (!ctx)
    {
        LOG_ERROR("Error during context init in RSA decrypt: " << getOpenSSLError());
        return 0;
    }
    if (EVP_PKEY_decrypt_init(ctx) <= 0)
    {
        LOG_ERROR("Error during EVP_PKEY_decrypt_init(ctx) in RSA decrypt: " << getOpenSSLError());
        return 0;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx, PADDING) <= 0)
    {
        LOG_ERROR("Error during EVP_PKEY_CTX_set_rsa_padding in RSA decrypt: " << getOpenSSLError());
        return 0;
    }
    if (EVP_PKEY_decrypt(ctx, plaintext, &plaintextLength, ciphertext, ciphertextLength) <= 0)
    {
        LOG_ERROR("Error during EVP_PKEY_decrypt in RSA decrypt: " << getOpenSSLError());
        return 0;
    }

    return plaintextLength;
}

} // namespace rsa

} // namespace butterfly

