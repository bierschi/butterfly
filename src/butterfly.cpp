
#include "butterfly.h"

namespace butterfly
{

Butterfly::Butterfly(int argc, char *argv[]) : _argparse(new butterfly::ArgumentParser())
{

    // parse args with the argument parser
    _args = _argparse->parseArgs(argc, argv);

    LOG_INFO("Running " << PROJECT_NAME << " with version " << _args._version);
    std::cout << "Running " << PROJECT_NAME << " with version " << _args._version << std::endl;
}

void Butterfly::run()
{

    // Start Encryption + Decryption
    if ( !_args._dir.empty() )
    {
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption+Decryption from directory " << _args._dir << std::endl;
        encryptor->invokeDir(_args._dir, _args._protected);

        //sleep(5);

        // start decryption
        std::shared_ptr<butterfly::hybrid::Decryptor> decryptor = std::make_shared<butterfly::hybrid::Decryptor>();
        decryptor->setDirPath(_args._dir);
        //decryptor->invokeDir("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");

        std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(8081);
        server->registerMasterPKeyCB(std::bind(&hybrid::Decryptor::invokeDir, decryptor, std::placeholders::_1));
        server->run();

    }
        // Start only Encryption
    else if ( !_args._encrypt.empty() )
    {

        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << _args._encrypt << std::endl;
        encryptor->invokeDir(_args._encrypt, _args._protected);

    }
        // Start only Decryption
    else if ( !_args._decrypt.empty() )
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption from directory " << _args._decrypt << std::endl;
        decryptor->setDirPath(_args._decrypt);
        decryptor->invokeDir(_args._serverpKey);
    } else
    {
        throw ButterflyException("Invalid usage of the Arguments!");
    }

}

} // namespace butterfly
