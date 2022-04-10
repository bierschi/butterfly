
#include "argumentParser.h"

namespace tools
{

ArgumentParser::ArgumentParser(int argc, char *argv[]) : _argc(argc), _argv(argv), _projectName("aesblfy")
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
        bool found = false, decrypt = false, key = false, iv = false, pair = false;
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

            } else if (arg == "-i" || arg == "--iv")
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

            } else if (arg == "-p" || arg == "--pair")
            {
                // check end of argc
                if (i + 1 < _argc && (!strchr(_argv[i + 1], '-')))
                {
                    found = true;
                    pair = true;
                    args.pair = _argv[i + 1];;

                }

            } else if (arg == "--hex")
            {
                found = true;
                args.hex = true;

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
        } else if ( (decrypt && ((!key or !iv) and !pair)) )
        {
            std::cout << "--decrypt option needs --key and --iv arguments or only --pair argument" << std::endl;
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
                 + std::string(_projectName) + " --encrypt 5357083.pdf \n\t"
                 + std::string(_projectName) + " --decrypt 5357083.pdf.bfly --key AESKey.txt --iv AESIV.txt\n\t"
                 + std::string(_projectName) + " --decrypt 5357083.pdf.bfly --key AESKeyHex.txt --iv AESIVHex.txt --hex\n\t"
                 + std::string(_projectName) + " --decrypt 5357083.pdf.bfly --pair AES.bin.unencrypted\n\n"

                 + "Options:\n"
                 + "\t-enc, --encrypt\t    Encrypts the file with AES\n"
                 + "\t-dec, --decrypt\t    Decrypts the file with AES\n"
                 + "\t-k,   --key         Provide the AESKey for the Decryption\n"
                 + "\t-i,   --iv          Provide the AESIV for the Decryption\n"
                 + "\t-p,   --pair        Provide the AES Keypair(Key+IV) for the Decryption\n"
                 + "\t--hex               Provide the AESKey and AESIV as hex numbers\n"
                 + "\t-h,   --help\t    Show this message and quit"

                 + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
              << std::endl;
}

} // namespace tools
