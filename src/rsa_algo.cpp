//
// Created on 22.01.20.
//

#include "rsa_algo.h"

RSA* RSAAlgorithm::_keypair = NULL;
RSA* RSAAlgorithm::_privateKey = NULL;
RSA* RSAAlgorithm::_publicKey = NULL;

RSAAlgorithm::RSAAlgorithm() : _privateKeyStr(nullptr), _publicKeyStr(nullptr), _encrypt_len(0) {
    std::cout << "create class RSAAlgorithm" << std::endl;

    if (_keypair == NULL) {
        // generate rsa key pair
        if (generateKeyPair()) {
            // extract private and public rsa key
            extractKeys();
        }
    }

}

RSAAlgorithm::RSAAlgorithm(RSA *privateKey, RSA *publicKey) : _privateKeyStr(nullptr), _publicKeyStr(nullptr), _encrypt_len(0) {
    std::cout << "create class RSAAlgorithm" << std::endl;

    RSAAlgorithm::_privateKey = privateKey;
    RSAAlgorithm::_publicKey = publicKey;
}


RSAAlgorithm::~RSAAlgorithm() {
    RSA_free(_keypair);
    RSA_free(_privateKey);
    RSA_free(_publicKey);
    free(_privateKeyStr);
    free(_publicKeyStr);
}
RSA* RSAAlgorithm::getKeypair() {
    return RSA_generate_key(KEYSIZE, 17, NULL, NULL);

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
char* RSAAlgorithm::createRSAPrivateKeyStr() {
    std::cout << "create private key string" << std::endl;

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, _privateKey);

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPrivateKey(bioPrivate, _privateKey, NULL, NULL, 0, NULL, NULL);

    size_t privateKeylen = BIO_pending(bioPrivate);
    _privateKeyStr = (char*) calloc(privateKeylen+1, 1);
    BIO_read(bioPrivate, _privateKeyStr, privateKeylen);

    return _privateKeyStr;

}

char* RSAAlgorithm::createRSAPublicKeyStr() {
    std::cout << "create public key string" << std::endl;

    EVP_PKEY *pkey = EVP_PKEY_new();
    EVP_PKEY_assign_RSA(pkey, _publicKey);

    BIO *bioPublic = BIO_new(BIO_s_mem());
    PEM_write_bio_RSAPublicKey(bioPublic, _publicKey);
    size_t publicKeylen = BIO_pending(bioPublic);

    _publicKeyStr = (char*) calloc(publicKeylen+1, 1);
    BIO_read(bioPublic, _publicKeyStr, publicKeylen);

    return _publicKeyStr;
}

void RSAAlgorithm::createRSAPrivateKeyFile(const std::string& filename) {

    FILE *privateKeyFile = fopen(filename.c_str(), "wb");

    if (privateKeyFile) {
        // PEM_write_PrivateKey(privateKeyFile, pkey, NULL, NULL, 0, NULL, NULL);
        PEM_write_RSAPrivateKey(privateKeyFile, _privateKey, NULL, NULL, 0, NULL, NULL);
        fclose(privateKeyFile);
    } else {
        std::cerr << "Unable to open file " << filename << " for writing private rsa key!" << std::endl;
    }

}

void RSAAlgorithm::createRSAPublicKeyFile(const std::string& filename) {

    FILE *publicKeyFile = fopen(filename.c_str(), "wb");
    if (publicKeyFile) {
        // PEM_write_PUBKEY(publicKeyFile, pkey);
        PEM_write_RSAPublicKey(publicKeyFile, _publicKey);
        fclose(publicKeyFile);
    } else {
        std::cerr << "Unable to open file " << filename << " for writing public rsa key!" << std::endl;
    }
}

RSA* RSAAlgorithm::getPublicKeyFromStr(const std::string& publicKeyStr) {

    RSA* publicKey;

    BIO *bioPublic = BIO_new(BIO_s_mem());
    BIO_write(bioPublic, publicKeyStr.c_str(), publicKeyStr.length());
    publicKey = PEM_read_bio_RSAPublicKey(bioPublic, NULL, NULL, NULL);
    BIO_free(bioPublic);

    return publicKey;
}

RSA* RSAAlgorithm::getPrivateKeyFromStr(const std::string& privateKeyStr) {

    RSA* privateKey;

    BIO *bioPrivate = BIO_new(BIO_s_mem());
    BIO_write(bioPrivate, privateKeyStr.c_str(), privateKeyStr.length());
    privateKey = PEM_read_bio_RSAPrivateKey(bioPrivate, NULL, NULL, NULL);

    BIO_free(bioPrivate);

    return privateKey;
}

RSA* RSAAlgorithm::getPublicKeyFromFile(const std::string& filepath) {

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

RSA* RSAAlgorithm::getPrivateKeyFromFile(const std::string& filepath) {

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

void RSAAlgorithm::encrypt() {

}


std::vector<std::string> RSAAlgorithm::messageChunks(const std::string &message) {

    std::vector<std::string> chunks;
    // create chunks of 256 bytes
    for (size_t i=0, j=0; i<ceil(message.length()/256.0); i++) {
        chunks.emplace_back(message.substr(j, 256));
        j=j+256;
    }
    return chunks;
}


char* RSAAlgorithm::encrypt(RSA* publicKey, const char* bytes) {

    // buffer for the modulus size n through RSA_size
    char* encrypt = static_cast<char*> (malloc(RSA_size(publicKey)));
    // buffer for the error message
    char* error = static_cast<char *>(malloc(130));

    // RSA_size() - 42 = 214
    if( (_encrypt_len = RSA_public_encrypt(RSA_size(publicKey)-42, (unsigned char*)bytes, (unsigned char*) encrypt,
                                           publicKey, RSA_PKCS1_OAEP_PADDING)) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), error);
        std::cerr << "Error encrypting bytes: " << error << std::endl;
    }
    std::cout << "encrypt_len: " << strlen(encrypt) << std::endl;
    return encrypt;
}

char* RSAAlgorithm::decrypt(RSA *privateKey, const char *encrypt) {

    // buffer for the decrypt chunks
    char* decrypt = static_cast<char *> (malloc(RSA_size(privateKey)));

    // buffer for the error message
    char* error = static_cast<char *>(malloc(130));
    int decryptLen;
    if ( (decryptLen = RSA_private_decrypt(RSA_size(privateKey), (unsigned char*)encrypt, (unsigned char*)decrypt,
                                  privateKey, RSA_PKCS1_OAEP_PADDING)) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), error);
        std::cerr << "Error decrypting bytes: " << error << std::endl;
    }

    std::cout << "decrypt_len: " << strlen(decrypt)+1 << std::endl;
    return decrypt;
}

void RSAAlgorithm::encryptFile(RSA *publicKey, const std::string &filepath) {

    std::ifstream in(filepath, std::ios_base::in | std::ios_base::binary);
    std::ofstream out(filepath + ".bin", std::ios_base::out | std::ios_base::binary | std::ios_base::app);
    char buf[256];

    while (!in.eof()) {

        in.read(&buf[0], 256);      // Read at most n bytes into
        std::cout << "bytes from encrypt file: " << in.gcount() << std::endl;
        char* data = encrypt(publicKey, &buf[0]);
        out.write(data, strlen(data)); // buf, then write the buf to
    }
    /*
    do {
        in.read(&buf[0], 256);      // Read at most n bytes into
        std::cout << "bytes from encrypt file: " << in.gcount() << std::endl;
        char* data = encrypt(publicKey, &buf[0]);
        out.write(data, strlen(data)); // buf, then write the buf to
        //writeFile(&buf[0], in.gcount());
    } while (in.gcount() > 0);          // the output.
     */
    in.close();
    out.close();
}

void RSAAlgorithm::decryptFile(RSA *privateKey, const std::string &filepath) {
    std::string newFile = filepath;
    std::ifstream in(filepath, std::ios_base::in | std::ios_base::binary);
    //size_t index = 0;
    //index = newFile.find(".bin", index);
    FILE *decrypted_file = fopen("decrypted_file.txt", "w");
    char buf[256];
    in.read(&buf[0], 256);
    std::cout << "bytes from decrypt file: " << in.gcount() << std::endl;
    char* dec = decrypt(privateKey, &buf[0]);
    fwrite(dec, 1, strlen(dec), decrypted_file);

    return;
    while (!in.eof()) {
        in.read(&buf[0], 256);
        std::cout << "bytes from decrypt file: " << in.gcount() << std::endl;
        char* dec = decrypt(privateKey, &buf[0]);
        fwrite(dec, 1, strlen(dec), decrypted_file);
    }

    fclose(decrypted_file);
    /*
    //newFile.replace(index, 4, "");
    std::ofstream out("decrypt.txt", std::ios_base::out | std::ios_base::app);
    char buf[256];

    do {
        in.read(&buf[0], 256);      // Read at most n bytes into
        std::cout << "bytes from decrypt file: " <<  in.gcount() << std::endl;
        char* data = decrypt(privateKey, &buf[0]);
        out.write(data, strlen(data)); // buf, then write the buf to
        //writeFile(&buf[0], in.gcount());
    } while (in.gcount() > 0);          // the output.
    in.close();
    out.close();
    */
}












void RSAAlgorithm::encryptMessage(RSA *publicKey, const std::string& message) {

    std::vector<std::string> chunks = messageChunks(message);
    FILE* out = fopen("out.txt", "a+");

    for (auto& chunk: chunks) {

        // buffer for the modulus size n through RSA_size
        char* encrypt = static_cast<char *> (malloc(RSA_size(publicKey)));
        // buffer for the error message
        char* error = static_cast<char *>(malloc(130));

        // RSA_size() - 42 = 214
        if( (_encrypt_len = RSA_public_encrypt(214, (unsigned char*)chunk.c_str(), (unsigned char*)encrypt,
                                               publicKey, RSA_PKCS1_OAEP_PADDING)) == -1) {
            ERR_load_crypto_strings();
            ERR_error_string(ERR_get_error(), error);
            fprintf(stderr, "Error encrypting message: %s\n", error);
        }
        if (out) {
            fwrite(encrypt, sizeof(*encrypt), RSA_size(publicKey), out);
            std::cout << "enc_to_file: " << sizeof(encrypt) << std::endl;
            std::cout<< "Encrypted message written to file" << std::endl;
            free(encrypt);
            encrypt = NULL;
        }
    }

    fclose(out);
}

void RSAAlgorithm::decrypt() {

}

void RSAAlgorithm::decryptMessage(RSA *privateKey) {

    std::cout << "Reading encrypted file" << std::endl;

    size_t  nread;
    char* encrypt = static_cast<char *> (malloc(RSA_size(privateKey)));
    char* decrypt = static_cast<char *> (malloc(RSA_size(privateKey)));

    FILE *in = fopen("out.txt", "rb");

    if (!in) {
        std::cerr << "error open decrpyt file" << std::endl;
    }
    while (!feof(in)) {
        while ( (nread = fread(encrypt,  1, RSA_size(privateKey), in)) > 0) {
            std::cout << "test"<< std::endl;
            //decrypt=NULL;
            //encrypt=NULL;
            //free(decrypt);
            //decrypt=NULL;
            int len = RSA_private_decrypt(256, (unsigned char*)encrypt, (unsigned char*)decrypt,
                                          privateKey, RSA_PKCS1_OAEP_PADDING);
            printf("Decrypted message: %s\n", decrypt);
        }

    }


    /*
    fread(encrypt, sizeof(encrypt), RSA_size(privateKey), in);
    std::cout << "size: " << sizeof(encrypt) << std::endl;
    fclose(in);
    char* err = static_cast<char *>(malloc(130));

    char* decrypt = static_cast<char *> (malloc(RSA_size(privateKey)));
    std::cout << "DDDD: " << sizeof(decrypt) << std::endl;

    int len = RSA_private_decrypt(256, (unsigned char*)encrypt, (unsigned char*)decrypt,
                        privateKey, RSA_PKCS1_OAEP_PADDING);
    std::cout << "len: " << len << std::endl;
    if(RSA_private_decrypt(256, (unsigned char*)encrypt, (unsigned char*)decrypt,
                           privateKey, RSA_PKCS1_OAEP_PADDING) == -1) {
        ERR_load_crypto_strings();
        ERR_error_string(ERR_get_error(), err);
        fprintf(stderr, "Error decrypting message: %s\n", err);
    }*/
    fclose(in);
    //printf("Decrypted message: %s\n", decrypt);
}