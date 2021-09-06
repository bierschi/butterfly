
#include "argumentParser.h"

namespace butterfly
{

ArgumentParser::ArgumentParser()
{

    // Logger is disabled as default setting
    Logger::disable();

    _usage = "Usage: \n \t\t" + std::string(PROJECT_NAME) +
             " --dir /home/christian/test/ --config /path/to/config\n\nOptions\n";
    _help = "-h, --help\t\tPrint help message\n";
    _version = "-v, --version\tPrint current version";

}

ArgumentParser::Arguments ArgumentParser::parseArgs(const int &argc, char *argv[])
{

    Arguments args;
    if (argc > 1)
    {

        for (int i = 1; i < argc; i++)
        {

            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help")
            {
                printHelp();
            } else if (arg == "-v" || arg == "--version")
            {
                printVersion();
            } else if (arg == "-c" || arg == "--config")
            {

                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    std::string configPath = argv[i + 1];

                    // init logger instance
                    Logger::initFromConfig(configPath);

                } else
                {
                    std::cout << "--config option requires one argument!" << std::endl;
                    break;
                }
            } else if (arg == "-d" || arg == "--dir")
            {
                // check end of argc
                if (i + 1 < argc && (!strchr(argv[i + 1], '-')))
                {
                    args._dir = argv[i + 1];

                } else
                {
                    std::cout << "--dir option requires one argument!" << std::endl;
                    break;
                }

            }
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
    output += _usage + _help + _version;
    std::cout << output << std::endl;
}

void ArgumentParser::printVersion()
{
    std::cout << PROJECT_NAME << " version " << PROJECT_VER << std::endl;
}

} // namespace butterfly