
#include "argumentParser.h"

namespace tools
{

ArgumentParser::ArgumentParser(int argc, char *argv[]) : _argc(argc), _argv(argv), _projectName("rsablfy")
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
        bool found = false, decrypt = false, key = false, ek = false, iv = false, pair = false;
        for (int i = 1; i < _argc; i++)
        {

            std::string arg = _argv[i];

            if (arg == "-h" || arg == "--help")
            {
                showUsage();
                exit(1);

            } else if (arg == "-enc" || arg == "--encrypt")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    args.encrypt = _argv[i + 1];

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
                    found = true;
                    decrypt = true;
                    args.decrypt = _argv[i + 1];

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
                    found = true;
                    key = true;
                    args.key = _argv[i + 1];

                } else
                {
                    std::cout << "--key option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-e" || arg == "--ek")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    ek = true;
                    args.ek = _argv[i + 1];

                } else
                {
                    std::cout << "--ek option requires one argument!" << std::endl;
                    exit(1);
                }

            }else if (arg == "-i" || arg == "--iv")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    iv = true;
                    args.iv = _argv[i + 1];

                } else
                {
                    std::cout << "--iv option requires one argument!" << std::endl;
                    exit(1);
                }

            } else if (arg == "-p" || arg == "--ekivpair")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    pair = true;
                    args.ekivpair = _argv[i + 1];;

                } else
                {
                    std::cout << "--ekivpair option requires one argument!" << std::endl;
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
        } else if ( (decrypt && ((!key or !iv or !ek) and !pair)) )
        {
            std::cout << "--decrypt option needs --key and --iv with --ek arguments or with --ekivpair argument" << std::endl;
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
                 + std::string(_projectName) + " --encrypt message.txt\n\t"
                 + std::string(_projectName) + " --encrypt testmessage\n\t"
                 + std::string(_projectName) + " --decrypt encrypted.bin --key RSAPrivateKey.pem --ek rsa_ek.bin --iv rsa_iv.txt\n\t"
                 + std::string(_projectName) + " --decrypt CPrivateRSA.bin --key SPrivateRSA.pem --ek rsa_ek.bin --iv rsa_iv.txt\n\t"
                 + std::string(_projectName) + " --decrypt CPrivateRSA.bin --key SPrivateRSA.pem --ekivpair RSA.bin\n\n"

                 + "Options:\n"
                 + "\t-enc, --encrypt\t    Encrypts the file/msg with RSA\n"
                 + "\t-dec, --decrypt\t    Decrypts the file with RSA\n"
                 + "\t-k,   --key         Provide the RSAPrivateKey for the Decryption\n"
                 + "\t-e,   --ek          Provide the RSAEK for the Decryption\n"
                 + "\t-i,   --iv          Provide the RSAIV for the Decryption\n"
                 + "\t-p,   --ekivpair    Provide the RSA Keypair(EK+IV) for the Decryption\n"
                 + "\t-h,   --help\t    Show this message and quit"

                 + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
              << std::endl;
}

} // namespace tools
