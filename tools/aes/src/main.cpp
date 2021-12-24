
#include <memory>
#include <unistd.h>

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

    std::string fileData = readBinFile(filename);

    unsigned char *encryptedFile;
    size_t encryptedFileLength = cryptoAES->encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    writeBinFile(filename + BFLY_FILE_EXTENSION, reinterpret_cast<const char *>(encryptedFile), static_cast<long>(encryptedFileLength));

    std::string aeskey = cryptoAES->getAESKey();
    std::string aesiv = cryptoAES->getAESIv();
    writeBinFile(AESKEY_FILENAME, aeskey.c_str(), aeskey.length());
    writeBinFile(AESIV_FILENAME, aesiv.c_str(), aesiv.length());

    std::string aeskeyhex = string2Hex(aeskey);
    std::string aesivhex = string2Hex(aesiv);
    writeBinFile(AESKEY_HEX_FILENAME, aeskeyhex.c_str(), aeskeyhex.length());
    writeBinFile(AESIV_HEX_FILENAME, aesivhex.c_str(), aesivhex.length());

}

void decrypt_with_aes(const std::string &filename)
{

    std::shared_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());

    std::string fileDataBfly = readBinFile(filename + BFLY_FILE_EXTENSION);
    std::string aeskey = readBinFile(AESKEY_FILENAME);
    std::string aesiv  = readBinFile(AESIV_FILENAME);

    cryptoAES->setAESKey(aeskey);
    cryptoAES->setAESIv(aesiv);

    unsigned char *decryptedFile;
    size_t decryptedFileLength = cryptoAES->decrypt((unsigned char *) fileDataBfly.c_str(), fileDataBfly.length(), &decryptedFile);

    writeBinFile(filename + ".dec", reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));

}

int main (int argc, char* argv[])
{

    std::string filename = "hello.txt";

    encrypt_with_aes(filename);
    decrypt_with_aes(filename);

    return 0;
}