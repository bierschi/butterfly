
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



RSA* CryptoRSA::getPublicKeyFromFile(const std::string& filepath) {

    RSA *publicKey = NULL;
    FILE *publicFile = fopen(filepath.c_str(), "rb");

    if (publicFile) {
        /*
        EVP_PKEY *pkey = EVP_PKEY_new();
        EVP_PKEY_assign_RSA(pkey, publicKey);

        if (PEM_read_PUBKEY(publicFile, &pkey, NULL, NULL) != NULL) {
            LOG_ERROR("TESTERROR")
        }
        publicKey = EVP_PKEY_get1_RSA(pkey);
        */

        if (PEM_read_RSAPublicKey(publicFile, &publicKey, NULL, NULL) != NULL) {
            LOG_ERROR("TESTERROR")
        }
        fclose(publicFile);
    } else {
        LOG_ERROR("PUBLIC KEY ERROR")
        //std::cerr << "Error opening public key file" << std::endl;
    }

    return publicKey;
}

RSA* CryptoRSA::getPrivateKeyFromFile(const std::string& filepath) {

    RSA *privateKey = NULL;
    FILE *privateFile = fopen(filepath.c_str(), "rb");

    if (privateFile) {
        if (PEM_read_RSAPrivateKey(privateFile, &privateKey, NULL, NULL) != NULL) {
        }
        fclose(privateFile);
    } else {
        //std::cerr << "Error opening private key file" << std::endl;
    }
    return privateKey;
}



char* CryptoRSA::encrypt(RSA *publicKey, const char *plaintext) {

    // buffer for the modulus size n through RSA_size
    char* encrypt = static_cast<char*> (malloc(static_cast<size_t>(RSA_size(publicKey))));

    // buffer for the error message
    char* error = static_cast<char *>(malloc(130));
    int encryptLen;
    if( (encryptLen = RSA_public_encrypt(static_cast<int>(strlen(plaintext)), (unsigned char*)plaintext, (unsigned char*) encrypt,
                                         publicKey, RSA_PKCS1_OAEP_PADDING)) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), error);
        LOG_ERROR("ERROR: " << error);
        //std::cerr << "Error encrypting plaintext: " << error << std::endl;
    }
    LOG_INFO("ENCRYPT: " << encrypt);
    LOG_INFO("LEN: " <<encryptLen);
    return encrypt;
}

char* CryptoRSA::decrypt(RSA *privateKey, const char *ciphertext) {

    // buffer for the decrypt chunks
    char* decrypt = static_cast<char *> (malloc(static_cast<size_t>(RSA_size(privateKey))));

    // buffer for the error message
    char* error = static_cast<char *>(malloc(130));
    int decryptLen;
    if ( (decryptLen = RSA_private_decrypt(RSA_size(privateKey), (unsigned char*)ciphertext, (unsigned char*)decrypt,
                                           privateKey, RSA_PKCS1_OAEP_PADDING)) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), error);
        LOG_ERROR("ERROR decrypt: " << error);
    }

    return decrypt;
}

} // namespace butterfly
