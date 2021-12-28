
#include "butterfly.h"

namespace butterfly
{

Butterfly::Butterfly(int argc, char *argv[]) : _argparse(new butterfly::ArgumentParser(argc, argv))
{

    // parse args with the argument parser
    _args = _argparse->parseArgs();

    // init logging
    initLoggingFramework();

}

void Butterfly::initLoggingFramework()
{
    // Logger is disabled as default setting
    #ifdef LOGGING
    Logger::disable();
    #endif

    if ( !_args.config.empty() )
    {
        // init logger instance
        #ifdef LOGGING
        Logger::initFromConfig(_args.config);
        #endif
    }
    
    #ifdef LOGGING
    LOG_INFO("Running " << PROJECT_NAME << " with version " << _args.version);
    #else
    std::cout << "Running " << PROJECT_NAME << " with version " << _args.version << std::endl;
    #endif
}

void Butterfly::run()
{

    // Start Encryption + Decryption
    if ( !_args.dir.empty() )
    {
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption+Decryption from directory " << _args.dir << std::endl;
        encryptor->invokeDir(_args.dir, _args.protection);

        //sleep(5);

        // start decryption
        std::shared_ptr<butterfly::hybrid::Decryptor> decryptor = std::make_shared<butterfly::hybrid::Decryptor>();
        decryptor->setDirPath(_args.dir);
        //decryptor->invokeDir("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");

        std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(8081);
        server->registerMasterPKeyCB(std::bind(&hybrid::Decryptor::invokeDir, decryptor, std::placeholders::_1));
        server->run();

    }
        // Start only Encryption
    else if ( !_args.encrypt.empty() )
    {

        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << _args.encrypt << std::endl;
        encryptor->invokeDir(_args.encrypt, _args.protection);

    }
        // Start only Decryption
    else if ( !_args.decrypt.empty() )
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption from directory " << _args.decrypt << std::endl;
        decryptor->setDirPath(_args.decrypt);
        decryptor->invokeDir(_args.serverpKey);
    } else
    {
        throw ButterflyException("Invalid usage of the Arguments!");
    }

}

} // namespace butterfly
