
#include "argumentParser.h"

namespace butterfly
{

ArgumentParser::ArgumentParser()
{

    // Logger is disabled as default setting
    Logger::disable();

    _usage     = "Usage: \n\t" + std::string(PROJECT_NAME) + " --dir /home/christian/test/ --config /path/to/config\n\t"
                               + std::string(PROJECT_NAME) + " --dir /home/christian/test/ --protected\n\n";

    _options   = "Options:\n";
    _dir       = "-d, --dir\t\tDirectory Path to start the encryption\n";
    _protected = "-p, --protected\t\tSave all key files to System\n";
    _config    = "-c, --config\t\tConfig Path\n";
    _help      = "-h, --help\t\tPrint help message\n";
    _version   = "-v, --version\t\tPrint current version";

}

ArgumentParser::Arguments ArgumentParser::parseArgs(const int &argc, char *argv[])
{

    Arguments args;
    if (argc > 1)
    {
        bool found = false;
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
                found = true;
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
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
                found = true;
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    args._dir = argv[i + 1];

                } else
                {
                    std::cout << "--dir option requires one argument!" << std::endl;
                    exit(1);
                }

            } else {

                if ( i < argc && (strchr(argv[i], '-')) )
                {
                    found = false;
                }

            }
        }
        if (!found)
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
    output += _usage + _options + _dir + _protected + _config + _help + _version;
    std::cout << output << std::endl;
}

void ArgumentParser::printVersion()
{
    std::cout << PROJECT_NAME << " version " << PROJECT_VER << std::endl;
}

} // namespace butterfly