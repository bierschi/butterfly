
#include <memory>

#include "argumentParser.h"
#include "crypto/encryptor.h"
#include "crypto/decryptor.h"

int main(int argc, char *argv[])
{
    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    butterfly::ArgumentParser::Arguments args = argparse->parseArgs(argc, argv);

    LOG_INFO("Running " << PROJECT_NAME << " with version " << args._version);
    std::cout << "Running " << PROJECT_NAME << " with version " << args._version << std::endl;

    // Start Encryption + Decryption
    if ( !args._dir.empty() )
    {
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption+Decryption from directory " << args._dir << std::endl;
        encryptor->invokeDir(args._dir, args._protected);

        sleep(5);

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

     return 0;
}