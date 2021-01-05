
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/rsaEncryptor.h"


void encrypt() {

    std::unique_ptr<butterfly::CryptoRSA> rsa(new butterfly::CryptoRSA());

    const char *plaintext = "Test message abc, Test message def, Test message ghi";

    EVP_PKEY *pkey = rsa->getPkeyFromPublicKeyFile("public.pem");

    int keysize = EVP_PKEY_size(pkey);
    LOG_TRACE("Keysize: " << keysize)

    unsigned char ciphertext[keysize];

    size_t ciphertext_len = rsa->encrypt(pkey, (unsigned char*)plaintext, strlen(plaintext)+1, ciphertext);
    LOG_TRACE("ciphertext length: " << ciphertext_len)

    FILE *out = fopen("file.bin","wb");
    fwrite(ciphertext, sizeof(char), ciphertext_len, out);
    //BIO_dump_fp (stdout, (const char *)ciphertext, (int)ciphertext_len);
    LOG_TRACE("Ciphertext: " << reinterpret_cast<char*>(ciphertext));
}

void decrypt() {
    std::unique_ptr<butterfly::CryptoRSA> rsa(new butterfly::CryptoRSA(2048));

    EVP_PKEY *pkey = rsa->getPkeyFromPrivateKeyFile("CPrivateRSA.pem");

    int keysize = EVP_PKEY_size(pkey);

    unsigned char buffer[keysize];
    unsigned char rsa_out[keysize] = {0};

    FILE *out = fopen("key.bin", "rb");
    fread(buffer, sizeof(buffer), 1, out);

    LOG_TRACE("Keysize: " << keysize)

    rsa->decrypt(pkey, buffer, (size_t)keysize, rsa_out);

    LOG_TRACE("Decrypted: " << reinterpret_cast<char*>(rsa_out));
}


int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << arg._version);
    //std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());

    std::unique_ptr<butterfly::RSAEncryptor> rsaEncryptor(new butterfly::RSAEncryptor(4096));

    //decrypt();

    sleep(2);

    rsaEncryptor->saveClientPrivateRSAKeyFile();
    rsaEncryptor->saveClientPublicKeyFile();

    std::string s_short = "0123456789abcdefghijk";

    rsaEncryptor->encrypt(s_short);

    //rsaEncryptor->decrypt()


    return 0;
}