
#include "argumentParser.h"

namespace butterfly
{

ArgumentParser::ArgumentParser()
{

    // Logger is disabled as default setting
    Logger::disable();

    _usage      = "Usage: \n\t" + std::string(PROJECT_NAME) + " --dir /home/butterfly/test/\n\t"
                                + std::string(PROJECT_NAME) + " --dir /home/butterfly/test/ --protected\n\t"
                                + std::string(PROJECT_NAME) + " --encrypt /home/butterfly/test/ \n\t"
                                + std::string(PROJECT_NAME) + " --decrypt /home/butterfly/test/ --key /home/butterfly/SPrivateRSA.pem\n\n";

    _options    = "Options:\n";
    _dir        = "-d, --dir\t\tDirectory Path to start the Encryption+Decryption\n";
    _encrypt    = "--encrypt\t\tEncrypts all files in provided directory\n";
    _decrypt    = "--decrypt\t\tDecrypts all files in provided diretory\n";
    _serverpKey = "-k, --key\t\tPrivate Key from the Server for the Decryption (Corresponds to the embedded Server Public Key)\n";
    _protected  = "-p, --protected\t\tSave all key files to System\n";
    _config     = "-c, --config\t\tConfig Path\n";
    _help       = "-h, --help\t\tPrint help Message\n";
    _version    = "-v, --version\t\tPrint current Version";

}

ArgumentParser::Arguments ArgumentParser::parseArgs(const int &argc, char *argv[])
{

    Arguments args;
    if (argc > 1)
    {
        bool found = false, decrypt = false, key = false;
        for (int i = 1; i < argc; i++)
        {

            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help")
            {
                printHelp();
                exit(1);

            } else if (arg == "-v" || arg == "--version")
            {
                printVersion();
                exit(1);

            } else if (arg == "-p" || arg == "--protected")
            {
                found = true;
                args._protected = true;
            }
            else if (arg == "-c" || arg == "--config")
            {
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    found = true;
                    std::string configPath = argv[i + 1];

                    // init logger instance
                    Logger::initFromConfig(configPath);

                } else
                {
                    std::cout << "--config option requires one argument!" << std::endl;
                    exit(1);
                }
            } else if (arg == "-d" || arg == "--dir")
            {
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    found = true;
                    args._dir = argv[i + 1];

                } else
                {
                    std::cout << "--dir option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "--encrypt")
            {
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    found = true;
                    args._encrypt = argv[i + 1];

                } else
                {
                    std::cout << "--encrypt option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "--decrypt")
            {
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    found = true, decrypt = true;
                    args._decrypt = argv[i + 1];

                } else
                {
                    std::cout << "--decrypt option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-k" || arg == "--key")
            {
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    found = true, key = true;
                    args._serverpKey = argv[i + 1];

                } else
                {
                    std::cout << "--key option requires one argument!" << std::endl;
                    exit(1);
                }

            } else {

                if ( i + 1 < argc && (!strchr(argv[i + 1], '-')) )
                {
                    found = false;
                }

            }
        }
        if (!found or (!decrypt && key) or (decrypt && !key))
        {
            printHelp();
            exit(1);
        }
    } else
    {
        printHelp();
        exit(1);
    }
    return args;
}

void ArgumentParser::printHelp()
{

    std::string output;
    output += _usage + _options + _dir + _encrypt + _decrypt + _serverpKey +  _protected + _config + _help + _version;
    std::cout << output << std::endl;
}

void ArgumentParser::printVersion()
{
    std::cout << PROJECT_NAME << " version " << PROJECT_VER << std::endl;
}

} // namespace butterfly