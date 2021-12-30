
#include "rsa.h"

namespace tools
{

CryptoRSA::CryptoRSA(int keysize) :  _keysize(keysize), _pkey(nullptr)
{
    // Initalize contexts
    rsaEncryptContext = EVP_CIPHER_CTX_new();
    rsaDecryptContext = EVP_CIPHER_CTX_new();


    // Generate the RSA Key
    if ( !generateRSAKey() )
    {
        #ifdef LOGGING
        std::cerr << "Error at generating the RSA key!" << std::endl;
        #endif
        throw std::runtime_error("Error at generating the RSA key!");
    }
}

CryptoRSA::CryptoRSA(const std::string &key) : _keysize(-1), _pkey(nullptr)
{
    // Initalize contexts
    rsaEncryptContext = EVP_CIPHER_CTX_new();
    rsaDecryptContext = EVP_CIPHER_CTX_new();

    // Load pkey from file or string
    if ( !loadKeyFromFile(key) )
    {
        #ifdef LOGGING
        std::cerr << "Could not load key from file/string!" << std::endl;
        #endif
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

    if ( existsFile(filepath) )
    {
        if ( loadKeyFromStr(readBinFile(filepath)) )
        {
            #ifdef LOGGING
            std::cerr << "Loaded successfully rsa key from file " << filepath << std::endl;
            #endif
            return true;
        }
    } else
    {
        if ( loadKeyFromStr(filepath) )
        {
            #ifdef LOGGING
            std::cerr << "Loaded successfully rsa key from string!" << std::endl;
            #endif
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
        #ifdef LOGGING
        std::cerr << "Unsupported file provided with file header: " << fLine << std::endl;
        #endif
        BIO_free(bioPrivate);
        return false;
    }

    BIO_free(bioPrivate);

    return true;
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

int CryptoRSA::encryptEVP(EVP_PKEY *key, const unsigned char *message, size_t messageLength, unsigned char **encryptedMessage,
                          unsigned char **encryptedKey, size_t *encryptedKeyLength, unsigned char **iv)
{

    // Allocate memory for everything
    size_t encryptedMessageLength = 0;
    size_t blockLength = 0;

    *encryptedKey = (unsigned char*)malloc(EVP_PKEY_size(key));
    *iv = (unsigned char*)malloc(EVP_MAX_IV_LENGTH);

    *encryptedMessage = (unsigned char*)malloc(messageLength + EVP_MAX_IV_LENGTH);

    if(!EVP_SealInit(rsaEncryptContext, EVP_aes_256_cbc(), encryptedKey, (int*)encryptedKeyLength, *iv, &key, 1))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_SealInit in RSA encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }

    if(!EVP_SealUpdate(rsaEncryptContext, *encryptedMessage + encryptedMessageLength, (int*)&blockLength, (const unsigned char*)message, (int)messageLength))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_SealUpdate in RSA encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    encryptedMessageLength += blockLength;

    if(!EVP_SealFinal(rsaEncryptContext, *encryptedMessage + encryptedMessageLength, (int*)&blockLength))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_SealFinal in RSA encrypt: " << getOpenSSLError() <<std::endl;
        #endif
        return -1;
    }
    encryptedMessageLength += blockLength;

    return (int)encryptedMessageLength;
}

int CryptoRSA::decryptEVP(EVP_PKEY *key, unsigned char *encryptedMessage, size_t encryptedMessageLength, unsigned char *encryptedKey,
                          size_t encryptedKeyLength, unsigned char *iv, unsigned char **decryptedMessage)
{

    // Allocate memory for everything
    size_t decryptedMessageLength = 0;
    size_t blockLength = 0;

    *decryptedMessage = (unsigned char*)malloc(encryptedMessageLength + EVP_MAX_IV_LENGTH);

    // Decrypt it!
    if(!EVP_OpenInit(rsaDecryptContext, EVP_aes_256_cbc(), encryptedKey, getEvpPkeySize(key), iv, key))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_OpenInit in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }

    if(!EVP_OpenUpdate(rsaDecryptContext, (unsigned char*)*decryptedMessage + decryptedMessageLength, (int*)&blockLength, encryptedMessage, (int)encryptedMessageLength))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_OpenUpdate in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    decryptedMessageLength += blockLength;

    if(!EVP_OpenFinal(rsaDecryptContext, (unsigned char*)*decryptedMessage + decryptedMessageLength, (int*)&blockLength))
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_OpenFinal in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    decryptedMessageLength += blockLength;

    return (int)decryptedMessageLength;
}


int CryptoRSA::encrypt(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char *ciphertext)
{

    EVP_PKEY_CTX *ctx;
    size_t ciphertextLength;
    ctx = EVP_PKEY_CTX_new(key, nullptr);

    if (!ctx)
    {
        #ifdef LOGGING
        std::cerr << "Error during context init in RSA encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    if (EVP_PKEY_encrypt_init(ctx) <= 0)
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_PKEY_encrypt_init(ctx) in RSA encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx, PADDING) <= 0)
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_PKEY_CTX_set_rsa_padding in RSA encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    if (EVP_PKEY_encrypt(ctx, ciphertext, &ciphertextLength, plaintext, plaintextLength) <= 0)
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_PKEY_encrypt in RSA encrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }

    return static_cast<int>(ciphertextLength);

}

int CryptoRSA::decrypt(EVP_PKEY *key, unsigned char *ciphertext, size_t ciphertextLength, unsigned char *plaintext)
{

    EVP_PKEY_CTX *ctx;
    size_t plaintextLength;
    ctx = EVP_PKEY_CTX_new(key, nullptr);

    if (!ctx)
    {
        #ifdef LOGGING
        std::cerr << "Error during context init in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    if (EVP_PKEY_decrypt_init(ctx) <= 0)
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_PKEY_decrypt_init(ctx) in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx, PADDING) <= 0)
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_PKEY_CTX_set_rsa_padding in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }
    if (EVP_PKEY_decrypt(ctx, plaintext, &plaintextLength, ciphertext, ciphertextLength) <= 0)
    {
        #ifdef LOGGING
        std::cerr << "Error during EVP_PKEY_decrypt in RSA decrypt: " << getOpenSSLError() << std::endl;
        #endif
        return -1;
    }

    return static_cast<int>(plaintextLength);
}

} // namespace tools
