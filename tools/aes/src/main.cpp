#include <memory>
#include <unistd.h>
#include <algorithm>

#include "aes.h"
#include "utils.h"

#define BFLY_FILE_EXTENSION ".bfly"
#define AESKEY_FILENAME     "AESKey.txt"
#define AESIV_FILENAME      "AESIV.txt"
#define AESKEY_HEX_FILENAME "AESKeyHex.txt"
#define AESIV_HEX_FILENAME  "AESIVHex.txt"

void encrypt_with_aes(const std::string &filename)
{
    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::cout << "Encrypting file " << filename << " with AES..." << std::endl;

    std::string fileData = readBinFile(filename);

    unsigned char *encryptedFile;
    size_t encryptedFileLength = cryptoAES->encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    writeBinFile(filename + BFLY_FILE_EXTENSION, reinterpret_cast<const char *>(encryptedFile), static_cast<long>(encryptedFileLength));

    std::cout << "Successfully encrypted file " << filename + BFLY_FILE_EXTENSION << " with size of " << std::fixed << std::setprecision(2) << getFileSize(filename, false) << " Bytes" << std::endl;

    std::string aeskey = cryptoAES->getAESKey();
    std::string aesiv = cryptoAES->getAESIv();
    writeBinFile(AESKEY_FILENAME, aeskey.c_str(), aeskey.length());
    writeBinFile(AESIV_FILENAME, aesiv.c_str(), aesiv.length());

    std::string aeskeyhex = string2Hex(aeskey);
    std::string aesivhex = string2Hex(aesiv);
    writeBinFile(AESKEY_HEX_FILENAME, aeskeyhex.c_str(), aeskeyhex.length());
    writeBinFile(AESIV_HEX_FILENAME, aesivhex.c_str(), aesivhex.length());

}

void decrypt_with_aes(const std::string &filename, const std::string &aeskeyFile, const std::string &aesivFile, bool hex)
{
    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::cout << "Decrypting file " << filename << " with AES..." << std::endl;

    std::string fileDataBfly = readBinFile(filename);

    std::string aeskey = readBinFile(aeskeyFile);
    std::string aesiv  = readBinFile(aesivFile);

    if (hex)
    {
        aeskey = hex2String(aeskey);
        aesiv  = hex2String(aesiv);
    }

    cryptoAES->setAESKey(aeskey);
    cryptoAES->setAESIv(aesiv);

    unsigned char *decryptedFile;
    size_t decryptedFileLength = cryptoAES->decrypt((unsigned char *) fileDataBfly.c_str(), fileDataBfly.length(), &decryptedFile);

    if (decryptedFileLength == 0)
    {
        exit(1);
    }

    writeBinFile(filename + ".dec", reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));

    std::cout << "Successfully decrypted file " << filename << " with size of " << std::fixed << std::setprecision(2) << getFileSize(filename, false) << " Bytes" << std::endl;
}

void showUsage()
{
    std::cout << "Usage: \n\t"
                 + std::string("aesbfly") + " --encrypt 5357083.pdf \n\t"
                 + std::string("aesbfly") + " --decrypt --key AESKey.txt --iv AESIV.txt 5357083.pdf.bfly \n\n"

                 + "Options:\n"
                 + "\t-enc, --encrypt\t    Encrypts the file with AES\n"
                 + "\t-dec, --decrypt\t    Decrypts the file with AES\n"
                 + "\t-k,   --key         Provide the AESKey for the Decryption\n"
                 + "\t-i,   --iv          Provide the AESIV for the Decryption\n"
                 + "\t--hex               Provide the AESKey and AESIV as hex numbers\n"
                 + "\t-h,   --help\t    Show this message and quit"

                 + "\n\nbutterfly homepage at: https://github.com/bierschi/butterfly"
              << std::endl;
}

int main (int argc, char* argv[])
{

    if (argc < 2)
    {
        std::cerr << "No args present, aborting!" << std::endl;
        exit(1);
    }
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help")
        {
            showUsage();
            exit(1);

        }
        if (arg == "-enc" || arg == "--encrypt")
        {
            std::string filename = argv[i+1];
            if (existsFile(filename))
            {
                encrypt_with_aes(filename);
            }
            break;
        }
        else if (arg == "-dec" || arg == "--decrypt")
        {
            std::string key, iv;
            bool hex = false;
            for (int j=2; j < argc; j++)
            {
                std::string arg2 = argv[j];

                if (arg2 == "-k" || arg2 == "--key")
                {
                    key = argv[j+1];
                }
                if (arg2 == "-i" || arg2 == "--iv")
                {
                    iv = argv[j+1];
                }
                if (arg2 == "--hex")
                {
                    hex  = true;
                }
            }
            std::string filename = argv[argc-1];
            decrypt_with_aes(filename, key, iv, hex);

            break;
        } else
        {
            showUsage();
            exit(1);
        }

    }

    return 0;
}