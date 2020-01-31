//
// Created on 22.01.20.
//

#include "rsa_algo.h"

RSA* RSAAlgorithm::_keypair = NULL;

RSAAlgorithm::RSAAlgorithm() {

    if (_keypair == NULL) {
        generateKeyPair();
    }
    createPrivateKey(true);
    createPublicKey(true);
}

RSAAlgorithm::~RSAAlgorithm() {
    RSA_free(_keypair);
    free(_privateKey);
    free(_publicKey);
}

bool RSAAlgorithm::generateKeyPair() {

    _keypair = RSA_new();

    if (_keypair != NULL) {
        BIGNUM *e = BN_new();
        return e != NULL && BN_set_word(e, RSA_F4) && RSA_generate_key_ex(_keypair, KEYSIZE, e, NULL);
    } else {
        return false;
    }
}

void RSAAlgorithm::createPrivateKey(bool file) {

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, _keypair);

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bioPrivate, _keypair, NULL, NULL, 0, NULL, NULL);

    size_t privateKeylen = BIO_pending(bioPrivate);
    _privateKey = (char*) calloc(privateKeylen+1, 1);
    BIO_read(bioPrivate, _privateKey, privateKeylen);

    if (file) {

        FILE *privateKeyFile = fopen("privatekey.pem", "wb");
        if (!privateKeyFile) {
            std::cerr << "Unable to open \"pkey.pem\" for writing" << std::endl;
        } else {
            bool ret = PEM_write_PrivateKey(privateKeyFile, pkey, NULL, NULL, 0, NULL, NULL);
            //bool ret = PEM_write_RSAPrivateKey(privateKeyFile, _keypair, NULL, NULL, 0, NULL, NULL);
            fclose(privateKeyFile);
        }

        std::cout << _privateKey << std::endl;
        BIO_free_all(bioPrivate);
    }
}

void RSAAlgorithm::createPublicKey(bool file) {

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, _keypair);

    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bioPublic, _keypair);

    size_t publicKeylen = BIO_pending(bioPublic);

    _publicKey = (char*) calloc(publicKeylen+1, 1);
    BIO_read(bioPublic, _publicKey, publicKeylen);

    if (file) {

        FILE *publicKeyFile = fopen("publickey.pem", "wb");
        if (!publicKeyFile) {
            std::cerr << "Unable to open \"pkey.pem\" for writing" << std::endl;
        } else {
            bool ret = PEM_write_PUBKEY(publicKeyFile, pkey);
            //bool ret = PEM_write_RSAPublicKey(publicKeyFile, _keypair);

            fclose(publicKeyFile);
        }

        BIO_free_all(bioPublic);
    }

    std::cout << _publicKey << std::endl;
}

char* RSAAlgorithm::getPrivateKey() {
    return _privateKey;
}

char* RSAAlgorithm::getPublicKey() {
    return _publicKey;
}

void RSAAlgorithm::encrypt(std::vector<boost::filesystem::path>& files) {
    _files = files;
    for (auto& file: _files) {
        std::cout << file << std::endl;
    }
    //run();
    //join();
}

void RSAAlgorithm::decrypt() {
    EVP_PKEY *pkey = EVP_PKEY_new();
    _keypair = RSA_generate_key(KEYSIZE, 3, NULL, NULL);
    EVP_PKEY_assign_RSA(pkey, _keypair);
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PrivateKey(bio, pkey, NULL, NULL, 0, 0, NULL);
    PEM_write_bio_RSAPrivateKey(bio, _keypair, NULL, NULL, 0, NULL, NULL);
    int pem_pkey_size = BIO_pending(bio);
    char *pem_pkey = (char*) calloc((pem_pkey_size)+1, 1);
    BIO_read(bio, pem_pkey, pem_pkey_size);
    std::cout << _privateKey << std::endl;
    FILE *pkey_file = fopen("key2.pem", "wb");
    if (!pkey_file) {
        std::cerr << "Unable to open \"key.pem\" for writing." << std::endl;
        return ;
    }
    std::cout << pkey << std::endl;
    bool ret = PEM_write_PrivateKey(pkey_file, pkey, NULL, NULL, 0, NULL, NULL);
    fclose(pkey_file);


}

