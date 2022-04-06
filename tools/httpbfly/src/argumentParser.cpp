
#include "argumentParser.h"

namespace tools
{

ArgumentParser::ArgumentParser(int argc, char *argv[]) : _argc(argc), _argv(argv), _projectName("httpbfly")
{
    // Save all arguments in vector
    for(int i = 1; i < _argc; i++)
    {
        _args.emplace_back(_argv[i]);
    }

}

ArgumentParser::Arguments ArgumentParser::parseArgs()
{

    Arguments args;

    if (_argc > 1)
    {
        bool found = false, server = false, client = false, ip = false, port = false;
        for (int i = 1; i < _argc; i++)
        {

            std::string arg = _argv[i];

            if (arg == "-h" || arg == "--help")
            {
                showUsage();
                exit(1);

            } else if (arg == "-c" || arg == "--client")
            {

                found = true;
                client = true;
                args.client = true;

            } else if (arg == "-s" || arg == "--server")
            {

                found = true;
                server = true;
                args.server = true;

            } else if (arg == "-i" || arg == "--ip")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    ip = true;
                    args.ip = _argv[i + 1];

                } else
                {
                    std::cout << "--ip option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-p" || arg == "--port")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    port = true;
                    args.port = std::stoi(_argv[i + 1]);

                } else
                {
                    std::cout << "--port option requires one argument!" << std::endl;
                    exit(1);
                }

            } else
            {

                if ( i + 1 < _argc && (!strchr(_argv[i + 1], '-')) )
                {
                    found = false;
                }

            }
        }
        if (!found)
        {
            showUsage();
            exit(1);
        } else if ( ((server or client) && (( !port)) ))
        {
            std::cout << "--server and --client option needs --port argument!" << std::endl;
            exit(1);
        } else if ( !server and !client )
        {
            std::cout << "--server or --client option is mandatory!" << std::endl;
            exit(1);
        } else if ( client and (!ip) )
        {
            std::cout << "--client option needs --ip argument!" << std::endl;
            exit(1);
        }
    } else
    {
        showUsage();
        exit(1);
    }

    return args;
}

void ArgumentParser::showUsage() const
{
    std::cout << "Usage: \n\t"
                 + std::string(_projectName) + " --client --port 8080 \n\t"
                 + std::string(_projectName) + " --server --port 8080 \n\n"

                 + "Options:\n"
                 + "\t-c, --client\t    Creates a client socket\n"
                 + "\t-s, --server\t    Creates a server socket\n"
                 + "\t-p,   --port\t    Provide the port\n"
                 + "\t-h,   --help\t    Show this message and quit"

                 + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
              << std::endl;
}

} // namespace tools
