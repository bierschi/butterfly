
#include "butterfly.h"

namespace butterfly
{

Butterfly::Butterfly(int argc, char *argv[]) : _argparse(new butterfly::ArgumentParser(argc, argv))
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

void Butterfly::loadEncryptedFiles(std::string &, std::string &)
{

}

void Butterfly::checkInternetConnection()
{

}

void Butterfly::run()
{


}

} // namespace butterfly
