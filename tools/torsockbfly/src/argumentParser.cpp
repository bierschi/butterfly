
#include "argumentParser.h"

namespace tools
{

ArgumentParser::ArgumentParser(int argc, char *argv[]) : _argc(argc), _argv(argv), _projectName("torsockbfly")
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
        bool found = false, client = false, port = false, url = false;
        for (int i = 1; i < _argc; i++)
        {

            std::string arg = _argv[i];

            if (arg == "-h" || arg == "--help")
            {
                showUsage();
                exit(1);

            } else if (arg == "-c" || arg == "--client")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    client = true;
                    args.client = _argv[i + 1];

                } else
                {
                    std::cout << "--client option requires one argument!" << std::endl;
                    exit(1);
                }

            }  else if (arg == "-p" || arg == "--port")
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
        }

        if ( !client )
        {
            args.client = "127.0.0.1";

        }
        if ( !port )
        {
            args.port = 9050;
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
                 + std::string(_projectName) + " --client 127.0.0.1 --port 9050 --url icanhazip.com \n\t"
                 + std::string(_projectName) + " --url y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion\n\n"

                 + "Options:\n"
                 + "\t-c,   --client\t    Tor client connection\n"
                 + "\t-p,   --port\t    Port to the tor client\n"
                 + "\t-u    --url\t    Request given url\n"
                 + "\t-h,   --help\t    Show this message and quit"

                 + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
              << std::endl;
}

} // namespace tools
