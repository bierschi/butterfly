
#include "crypto/rsa.h"

namespace butterfly {

RSA* CryptoRSA::_rsa = nullptr;

CryptoRSA::CryptoRSA() {
    LOG_TRACE("Create class CryptoRSA")

    if (CryptoRSA::_rsa == nullptr) {
        if ( !generateRSAKey() ) {
            throw std::runtime_error("Could not generate the RSA key!");
        }
    }

}

CryptoRSA::~CryptoRSA() {
    RSA_free(CryptoRSA::_rsa);
    free(_rsaPrivateKeyStr);
    free(_rsaPublicKeyStr);
    free(_publicKeyStr);
}

bool CryptoRSA::generateRSAKey() {
    LOG_INFO("Generating the RSA key")
    CryptoRSA::_rsa = RSA_new();

    if (CryptoRSA::_rsa != nullptr) {
        BIGNUM *e = BN_new();
        return e != nullptr && BN_set_word(e, RSA_F4) && RSA_generate_key_ex(CryptoRSA::_rsa, KEYSIZE, e, nullptr);
    } else {
        return false;
    }
}

char* CryptoRSA::getRSAPrivateKey() {
    LOG_INFO("Generating the rsa private key string")

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, CryptoRSA::_rsa);

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bioPrivate, CryptoRSA::_rsa, nullptr, nullptr, 0, nullptr, nullptr);

    int privateKeylen = BIO_pending(bioPrivate);
    _rsaPrivateKeyStr = static_cast<char*>( calloc(static_cast<size_t>(privateKeylen+1), 1) );
    BIO_read(bioPrivate, _rsaPrivateKeyStr, privateKeylen);

    return _rsaPrivateKeyStr;
}

char* CryptoRSA::getRSAPublicKey() {
    LOG_INFO("Generating the rsa public key string")

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, CryptoRSA::_rsa);

    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bioPublic, CryptoRSA::_rsa);

    int publicKeylen = BIO_pending(bioPublic);
    _rsaPublicKeyStr =  static_cast<char*>( calloc(static_cast<size_t>( publicKeylen+1 ), 1) );
    BIO_read(bioPublic, _rsaPublicKeyStr, publicKeylen);

    return _rsaPublicKeyStr;
}

char* CryptoRSA::getPublicKey() {
    LOG_INFO("Generating the public key string")

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, CryptoRSA::_rsa);

    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bioPublic, pkey);

    int publicKeylen = BIO_pending(bioPublic);
    _publicKeyStr =  static_cast<char*>( calloc(static_cast<size_t>( publicKeylen+1 ), 1) );
    BIO_read(bioPublic, _publicKeyStr, publicKeylen);

    return _publicKeyStr;
}

void CryptoRSA::createRSAPrivateKeyFile(const std::string &filename) {

    FILE *privateKeyFile = fopen(filename.c_str(), "wb");

    if (privateKeyFile) {
        LOG_INFO("Creating the rsa private key file " << filename);
        PEM_write_RSAPrivateKey(privateKeyFile, CryptoRSA::_rsa, nullptr, nullptr, 0, nullptr, nullptr);
        fclose(privateKeyFile);
    } else {
        LOG_ERROR("Unable to open file " << filename << " for writing private rsa key!")
    }
}

void CryptoRSA::createRSAPublicKeyFile(const std::string &filename) {

    FILE *publicKeyFile = fopen(filename.c_str(), "wb");

    if (publicKeyFile) {
        LOG_INFO("Creating the rsa public key file " << filename);
        PEM_write_RSAPublicKey(publicKeyFile, CryptoRSA::_rsa);
        fclose(publicKeyFile);
    } else {
        LOG_ERROR("Unable to open file " << filename << " for writing public rsa key!")
    }
}

void CryptoRSA::createPublicKeyFile(const std::string &filename) {

    FILE *publicKeyFile = fopen(filename.c_str(), "wb");

    if (publicKeyFile) {
        LOG_INFO("Creating the public key file " << filename);
        EVP_PKEY *pkey = EVP_PKEY_new();
        EVP_PKEY_assign_RSA(pkey, CryptoRSA::_rsa);
        PEM_write_PUBKEY(publicKeyFile, pkey);

        fclose(publicKeyFile);
    } else {
        LOG_ERROR("Unable to open file " << filename << " for writing public key!")
    }
}

EVP_PKEY* CryptoRSA::getPkeyFromPrivateKeyFile(const std::string &filepath) {

    EVP_PKEY *pkey = nullptr;
    FILE *privateFile = fopen(filepath.c_str(), "rb");

    if (privateFile) {

        pkey = PEM_read_PrivateKey(privateFile, nullptr, nullptr, nullptr);

        fclose(privateFile);
    } else {
        LOG_ERROR("Could not open private key file " << filepath);
    }

    return pkey;
}

EVP_PKEY* CryptoRSA::getPkeyFromPublicKeyFile(const std::string &filepath) {

    EVP_PKEY *pkey = nullptr;
    FILE *publicKeyFile = fopen(filepath.c_str(), "rb");

    if (publicKeyFile) {

        pkey = PEM_read_PUBKEY(publicKeyFile, nullptr, nullptr, nullptr);
        if (pkey == NULL) {
            LOG_ERROR("EVP_PKEY could not be initialized!")
        }
    } else {
        LOG_ERROR("Could not open public key file " << filepath);
    }

    return pkey;
}


size_t CryptoRSA::encrypt(EVP_PKEY *key, const unsigned char *plaintext, size_t plaintextLength, unsigned char *ciphertext) {

    EVP_PKEY_CTX *ctx;
    size_t ciphertextLength;
    ctx = EVP_PKEY_CTX_new(key, NULL);

    if (!ctx) {
        LOG_ERROR(stderr);
        return 0;
    }
    if (EVP_PKEY_encrypt_init(ctx) <= 0) {
        LOG_ERROR(stderr);
        return 0;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0) {
        LOG_ERROR(stderr);
        return 0;
    }
    if (EVP_PKEY_encrypt(ctx, ciphertext, &ciphertextLength, plaintext, plaintextLength) <= 0) {
        LOG_ERROR(stderr);
        return 0;
    }

    return ciphertextLength;

}

size_t CryptoRSA::decrypt(EVP_PKEY *key, unsigned char* ciphertext, size_t ciphertextLength, unsigned char* plaintext) {

    EVP_PKEY_CTX *ctx;
    size_t plaintextLength;
    ctx = EVP_PKEY_CTX_new(key,NULL);

    if (!ctx) {
        LOG_ERROR(stderr);
        return 0;
    }
    if (EVP_PKEY_decrypt_init(ctx) <= 0) {
        LOG_ERROR(stderr);
        return 0;
    }
    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_OAEP_PADDING) <= 0) {
        LOG_ERROR(stderr);
        return 0;
    }
    if (EVP_PKEY_decrypt(ctx, plaintext, &plaintextLength, ciphertext, ciphertextLength) <= 0) {
        LOG_ERROR(stderr);
        return 0;
    }

    return plaintextLength;
}

} // namespace butterfly
