#include <memory>
#include <algorithm>

#include "argumentParser.h"
#include "aes.h"
#include "utils.h"

#define BFLY_FILE_EXTENSION ".bfly"
#define AESKEY_FILENAME     "AESKey.txt"
#define AESIV_FILENAME      "AESIV.txt"
#define AESKEY_HEX_FILENAME "AESKeyHex.txt"
#define AESIV_HEX_FILENAME  "AESIVHex.txt"

void encrypt_with_aesFile(const std::string &filename)
{
    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::cout << "Encrypting file " << filename << " with AES!" << std::endl;

    std::string encFile = filename + BFLY_FILE_EXTENSION;

    std::ifstream input(filename, std::ios::binary | std::ios::in);
    std::ofstream output(encFile, std::ios::binary | std::ios::out);


    cryptoAES->encryptFile(input, output);
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

void encrypt_with_aes(const std::string &filename)
{
    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::cout << "Encrypting file " << filename << " with AES!" << std::endl;

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

void decrypt_with_aes(const std::string &filename, std::string aeskey, std::string aesiv, bool hex)
{
    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::cout << "Decrypting file " << filename << " with AES!" << std::endl;

    std::string fileDataBfly = readBinFile(filename);

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

void decrypt_with_aesFile(const std::string &filename, std::string aeskey, std::string aesiv, bool hex)
{

    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::cout << "Decrypting file " << filename << " with AES!" << std::endl;

    if (hex)
    {
        aeskey = hex2String(aeskey);
        aesiv  = hex2String(aesiv);
    }

    cryptoAES->setAESKey(aeskey);
    cryptoAES->setAESIv(aesiv);


    std::string outputFileDec = filename + ".dec";
    std::ifstream input(filename, std::ios::binary | std::ios::in);
    std::ofstream output(outputFileDec, std::ios::binary | std::ios::out);


    cryptoAES->decryptFile(input, output);
    std::cout << "Successfully decrypted file " << filename << " with size of " << std::fixed << std::setprecision(2) << getFileSize(filename, false) << " Bytes" << std::endl;
}

int main (int argc, char* argv[])
{
    std::unique_ptr<tools::ArgumentParser> _argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = _argparse->parseArgs();

    if ( !args.encrypt.empty() )
    {

        if ( existsFile(args.encrypt) )
        {
            //encrypt_with_aes(args.encrypt);
            encrypt_with_aesFile(args.encrypt);
        } else
        {
            std::cerr << "File " << args.encrypt << " does not exist!" << std::endl;
        }

    } else if ( !args.decrypt.empty() )
    {

        if ( existsFile(args.decrypt) )
        {
            if ( !args.pair.empty() )
            {
                if ( existsFile(args.pair) )
                {
                    std::string keypair = readBinFile(args.pair);
                    if (keypair.length() == 48)
                    {
                        std::string key = keypair.substr(0, 32);
                        std::string iv = keypair.substr(32, 48);

                        //decrypt_with_aes(args.decrypt, key, iv, args.hex);
                        decrypt_with_aesFile(args.decrypt, key, iv, args.hex);
                    } else
                    {
                        std::cerr << "String length of keypair is unequal 48!. Exiting" << std::endl;
                        exit(1);
                    }
                } else
                {
                    std::cerr << "File " << args.pair << " does not exist!" << std::endl;
                }

            } else
            {
                //decrypt_with_aes(args.decrypt, readBinFile(args.key), readBinFile(args.iv), args.hex);
                decrypt_with_aesFile(args.decrypt, readBinFile(args.key), readBinFile(args.iv), args.hex);
            }

        } else
        {
            std::cerr << "File " << args.decrypt << " does not exist" << std::endl;
        }

    }

    return 0;
}