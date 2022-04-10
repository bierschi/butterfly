
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
        bool found = false, server = false, client = false, url = false, port = false, get = false, post = false;
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

            } else if (arg == "-u" || arg == "--url")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    url = true;
                    args.url = _argv[i + 1];

                } else
                {
                    std::cout << "--url option requires one argument!" << std::endl;
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

            } else if (arg == "-g" || arg == "--get")
            {

                found = true;
                get = true;
                args.get = true;

            } else if (arg == "-po" || arg == "--post")
            {

                found = true;
                post = true;
                args.post = true;

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
        } else if ( client and (!url) )
        {
            std::cout << "--client option needs --url argument!" << std::endl;
            exit(1);
        } else if (get and post)
        {
            std::cout << "Use either --get or --post option" << std::endl;
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
                 + std::string(_projectName) + " --get --client --url www.google.de --port 80 \n\t"
                 + std::string(_projectName) + " --post --client --url http://127.0.0.1:5000/decryption/ --port 5000 \n\t"
                 + std::string(_projectName) + " --server --port 8080 \n\n"

                 + "Options:\n"
                 + "\t-c,  --client\t    Creates an HTTP Client\n"
                 + "\t-s,  --server\t    Creates an HTTP Server\n"
                 + "\t-u,  --url\t        Provide the URL\n"
                 + "\t-p,  --port\t        Provide the port\n"
                 + "\t-g,  --get\t        HTTP GET Request\n"
                 + "\t-po, --post\t        HTTP POST Request\n"
                 + "\t-h,  --help\t        Show this message and quit"

                 + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
              << std::endl;
}

} // namespace tools
