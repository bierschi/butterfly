//
// Created on 22.01.20.
//

#include "rsa_algo.h"

RSA* RSAAlgorithm::_keypair = NULL;
RSA* RSAAlgorithm::_privateKey = NULL;
RSA* RSAAlgorithm::_publicKey = NULL;

RSAAlgorithm::RSAAlgorithm() {
    std::cout << "RSAAlgorithm" << std::endl;

    if (_keypair == NULL) {
        // generate rsa key pair
        if (generateKeyPair()) {
            // extract private and public rsa key
            extractKeys();
        }
        createPrivateKeyStr(true);
        createPublicKeyStr(true);
    }


    //readPublicKeyFile();

}

RSAAlgorithm::~RSAAlgorithm() {
    RSA_free(_keypair);
    RSA_free(_privateKey);
    RSA_free(_publicKey);
    free(_privateKeyStr);
    free(_publicKeyStr);
}

bool RSAAlgorithm::generateKeyPair() {
    std::cout << "generate RSA key pairs" << std::endl;

    _keypair = RSA_new();

    if (_keypair != NULL) {
        BIGNUM *e = BN_new();
        return e != NULL && BN_set_word(e, RSA_F4) && RSA_generate_key_ex(_keypair, KEYSIZE, e, NULL);
    } else {
        return false;
    }
}

bool RSAAlgorithm::extractKeys() {

    // extract private key from keypair
    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bioPrivate, _keypair, NULL, NULL, 0, NULL, NULL);
    PEM_read_bio_RSAPrivateKey(bioPrivate, &_privateKey, NULL, NULL);

    // extract public key from keypair
    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bioPublic, _keypair);
    PEM_read_bio_RSAPublicKey(bioPublic, &_publicKey, NULL, NULL);

}
void RSAAlgorithm::createPrivateKeyStr(bool file) {
    std::cout << "create private key string" << std::endl;

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, _privateKey);

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bioPrivate, _privateKey, NULL, NULL, 0, NULL, NULL);

    size_t privateKeylen = BIO_pending(bioPrivate);
    _privateKeyStr = (char*) calloc(privateKeylen+1, 1);
    BIO_read(bioPrivate, _privateKeyStr, privateKeylen);

    if (file) {
        FILE *privateKeyFile = fopen("id_rsa", "wb");

        if (privateKeyFile) {
            //bool ret = PEM_write_PrivateKey(privateKeyFile, pkey, NULL, NULL, 0, NULL, NULL);
            bool ret = PEM_write_RSAPrivateKey(privateKeyFile, _privateKey, NULL, NULL, 0, NULL, NULL);
            fclose(privateKeyFile);
            //std::cout << _privateKeyStr << std::endl;
            BIO_free_all(bioPrivate);
        } else {
            std::cerr << "Unable to open \"id_rsa\" for writing private rsa key!" << std::endl;
        }
    }
}

void RSAAlgorithm::createPublicKeyStr(bool file) {
    std::cout << "create public key string" << std::endl;

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, _publicKey);

    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bioPublic, _publicKey);
    size_t publicKeylen = BIO_pending(bioPublic);

    _publicKeyStr = (char*) calloc(publicKeylen+1, 1);
    BIO_read(bioPublic, _publicKeyStr, publicKeylen);

    if (file) {

        FILE *publicKeyFile = fopen("id_rsa.pub", "wb");
        if (publicKeyFile) {
            //bool ret = PEM_write_PUBKEY(publicKeyFile, pkey);
            bool ret = PEM_write_RSAPublicKey(publicKeyFile, _publicKey);
            fclose(publicKeyFile);
            //std::cout << _publicKeyStr << std::endl;
            BIO_free_all(bioPublic);
        } else {
            std::cerr << "Unable to open \"id_rsa.pub\" for writing public rsa key!" << std::endl;
        }
    }
}


void RSAAlgorithm::encrypt(std::vector<boost::filesystem::path>& files) {

}
void RSAAlgorithm::encrypt() {

}

void RSAAlgorithm::encrypt(RSA *publicKey) {
    char  msg[KEYSIZE/8];

    fgets(msg, KEYSIZE-1, stdin);
    msg[strlen(msg)-1] = '\0';

    char* encrypt = static_cast<char *> (malloc(RSA_size(publicKey)));

    char* err = static_cast<char *>(malloc(130));

    if( (_encrypt_len = RSA_public_encrypt(strlen(msg)+1, (unsigned char*)msg, (unsigned char*)encrypt,
                                           publicKey, RSA_PKCS1_OAEP_PADDING)) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), err);
        fprintf(stderr, "Error encrypting message: %s\n", err);
    }
    std::cout << encrypt << std::endl;
    FILE* out = fopen("out.txt", "w");
    fwrite(encrypt, sizeof(*encrypt), RSA_size(publicKey), out);
    fclose(out);
    std::cout<< "Encrypted message written to file" << std::endl;
    free(encrypt);
    encrypt = NULL;
}
void RSAAlgorithm::decrypt() {

}

void RSAAlgorithm::decrypt(RSA *privateKey) {

    std::cout << "Reading encrypted file" << std::endl;

    char* encrypt = static_cast<char *> (malloc(RSA_size(privateKey)));

    FILE *out = fopen("out.txt", "r");

    fread(encrypt, sizeof(encrypt), RSA_size(privateKey), out);

    fclose(out);
    char* err = static_cast<char *>(malloc(130));

    char* decrypt = static_cast<char *> (malloc(256));

    if(RSA_private_decrypt(256, (unsigned char*)encrypt, (unsigned char*)decrypt,
                           privateKey, RSA_PKCS1_OAEP_PADDING) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), err);
        fprintf(stderr, "Error decrypting message: %s\n", err);
    }
    printf("Decrypted message: %s\n", decrypt);
}

RSA* RSAAlgorithm::readPublicKeyFile(const std::string& filepath) {

    RSA *publicKey = NULL;
    FILE *publicFile = fopen(filepath.c_str(), "rb");

    if (publicFile) {
        if (PEM_read_RSAPublicKey(publicFile, &publicKey, NULL, NULL) != NULL) {

        }
        fclose(publicFile);
    } else {
        std::cerr << "Error opening public key file" << std::endl;
    }
    return publicKey;
}

RSA* RSAAlgorithm::readPrivateKeyFile(const std::string& filepath) {

    RSA *privateKey = NULL;
    FILE *privateFile = fopen(filepath.c_str(), "rb");

    if (privateFile) {
        if (PEM_read_RSAPrivateKey(privateFile, &privateKey, NULL, NULL) != NULL) {
        }
        fclose(privateFile);
    } else {
        std::cerr << "Error opening private key file" << std::endl;
    }
    return privateKey;
}

char* RSAAlgorithm::getPrivateKeyStr() {
    return _privateKeyStr;
}

char* RSAAlgorithm::getPublicKeyStr() {
    return _publicKeyStr;
}

RSA* RSAAlgorithm::getPrivateKey() {
    return _privateKey;
}

RSA* RSAAlgorithm::getPublicKey() {
    return _publicKey;
}