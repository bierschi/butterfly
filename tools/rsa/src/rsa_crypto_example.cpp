
#include "rsa_crypto_example.h"

EVP_PKEY* Crypto::localKeypair;

Crypto::Crypto()
{
    localKeypair = NULL;
    remotePublicKey = NULL;

#ifdef PSEUDO_CLIENT
    generateRsaKeypair(&remotePublicKey);
#endif

    init();
}

Crypto::Crypto(unsigned char *remotePublicKey, size_t remotePublicKeyLength)
{
    localKeypair = NULL;
    this->remotePublicKey = NULL;

    setRemotePublicKey(remotePublicKey, remotePublicKeyLength);
    init();
}

Crypto::~Crypto()
{
    EVP_PKEY_free(remotePublicKey);

    EVP_CIPHER_CTX_free(rsaEncryptContext);
    EVP_CIPHER_CTX_free(rsaDecryptContext);

}

int Crypto::init()
{
    // Initalize contexts
    rsaEncryptContext = EVP_CIPHER_CTX_new();
    rsaDecryptContext = EVP_CIPHER_CTX_new();

    // Check if any of the contexts initializations failed
    if(rsaEncryptContext == NULL || rsaDecryptContext == NULL )
    {
        return FAILURE;
    }

    // Generate RSA and AES keys
    generateRsaKeypair(&localKeypair);

    return SUCCESS;
}

int Crypto::generateRsaKeypair(EVP_PKEY **keypair) {
    EVP_PKEY_CTX *context = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);

    if(EVP_PKEY_keygen_init(context) <= 0) {
        return FAILURE;
    }

    if(EVP_PKEY_CTX_set_rsa_keygen_bits(context, RSA_KEYLEN) <= 0) {
        return FAILURE;
    }

    if(EVP_PKEY_keygen(context, keypair) <= 0) {
        return FAILURE;
    }

    EVP_PKEY_CTX_free(context);

    return SUCCESS;
}

int Crypto::rsaEncrypt(const unsigned char *message, size_t messageLength, unsigned char **encryptedMessage, unsigned char **encryptedKey,
                       size_t *encryptedKeyLength, unsigned char **iv, size_t *ivLength) {

    // Allocate memory for everything
    size_t encryptedMessageLength = 0;
    size_t blockLength = 0;

    *encryptedKey = (unsigned char*)malloc(EVP_PKEY_size(localKeypair));
    *iv = (unsigned char*)malloc(EVP_MAX_IV_LENGTH);
    *ivLength = EVP_MAX_IV_LENGTH;

    if(*encryptedKey == NULL || *iv == NULL) {
        return FAILURE;
    }

    *encryptedMessage = (unsigned char*)malloc(messageLength + EVP_MAX_IV_LENGTH);
    if(encryptedMessage == NULL) {
        return FAILURE;
    }

    // Encrypt it!
    if(!EVP_SealInit(rsaEncryptContext, EVP_aes_256_cbc(), encryptedKey, (int*)encryptedKeyLength, *iv, &localKeypair, 1)) {
        return FAILURE;
    }

    if(!EVP_SealUpdate(rsaEncryptContext, *encryptedMessage + encryptedMessageLength, (int*)&blockLength, (const unsigned char*)message, (int)messageLength)) {
        return FAILURE;
    }
    encryptedMessageLength += blockLength;

    if(!EVP_SealFinal(rsaEncryptContext, *encryptedMessage + encryptedMessageLength, (int*)&blockLength)) {
        return FAILURE;
    }
    encryptedMessageLength += blockLength;

    return (int)encryptedMessageLength;
}

int Crypto::rsaDecrypt(unsigned char *encryptedMessage, size_t encryptedMessageLength, unsigned char *encryptedKey,
                       size_t encryptedKeyLength, unsigned char *iv, size_t ivLength, unsigned char **decryptedMessage) {

    // Allocate memory for everything
    size_t decryptedMessageLength = 0;
    size_t blockLength = 0;

    *decryptedMessage = (unsigned char*)malloc(encryptedMessageLength + ivLength);
    if(*decryptedMessage == NULL) {
        return FAILURE;
    }

#ifdef PSEUDO_CLIENT
    EVP_PKEY *key = remotePublicKey;
#else
    EVP_PKEY *key = localKeypair;
#endif

    // Decrypt it!
    if(!EVP_OpenInit(rsaDecryptContext, EVP_aes_256_cbc(), encryptedKey, encryptedKeyLength, iv, key)) {
        return FAILURE;
    }

    if(!EVP_OpenUpdate(rsaDecryptContext, (unsigned char*)*decryptedMessage + decryptedMessageLength, (int*)&blockLength, encryptedMessage, (int)encryptedMessageLength)) {
        return FAILURE;
    }
    decryptedMessageLength += blockLength;

    if(!EVP_OpenFinal(rsaDecryptContext, (unsigned char*)*decryptedMessage + decryptedMessageLength, (int*)&blockLength)) {
        return FAILURE;
    }
    decryptedMessageLength += blockLength;

    return (int)decryptedMessageLength;
}

int Crypto::getRemotePublicKey(unsigned char **publicKey) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bio, remotePublicKey);
    return bioToString(bio, publicKey);
}

int Crypto::setRemotePublicKey(unsigned char *publicKey, size_t publicKeyLength) {
    BIO *bio = BIO_new(BIO_s_mem());

    if(BIO_write(bio, publicKey, publicKeyLength) != (int)publicKeyLength) {
        return FAILURE;
    }

    PEM_read_bio_PUBKEY(bio, &remotePublicKey, NULL, NULL);
    BIO_free_all(bio);

    return SUCCESS;
}

int Crypto::getLocalPublicKey(unsigned char **publicKey) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PUBKEY(bio, localKeypair);
    return bioToString(bio, publicKey);
}

int Crypto::getLocalPrivateKey(unsigned char **privateKey) {
    BIO *bio = BIO_new(BIO_s_mem());
    PEM_write_bio_PrivateKey(bio, localKeypair, NULL, NULL, 0, 0, NULL);
    return bioToString(bio, privateKey);
}

int Crypto::writeKeyToFile(FILE *file, int key) {
    switch(key) {
        case KEY_SERVER_PRI:
            if(!PEM_write_PrivateKey(file, localKeypair, NULL, NULL, 0, 0, NULL)) {
                return FAILURE;
            }
            break;

        case KEY_SERVER_PUB:
            if(!PEM_write_PUBKEY(file, localKeypair)) {
                return FAILURE;
            }
            break;

        case KEY_CLIENT_PUB:
            if(!PEM_write_PUBKEY(file, remotePublicKey)) {
                return FAILURE;
            }
            break;

        default:
            return FAILURE;
    }

    return SUCCESS;
}

int Crypto::bioToString(BIO *bio, unsigned char **string) {
    size_t bioLength = BIO_pending(bio);
    *string = (unsigned char*)malloc(bioLength + 1);

    if(string == NULL) {
        return FAILURE;
    }

    BIO_read(bio, *string, bioLength);

    // Insert the NUL terminator
    (*string)[bioLength] = '\0';

    BIO_free_all(bio);

    return (int)bioLength;
}
