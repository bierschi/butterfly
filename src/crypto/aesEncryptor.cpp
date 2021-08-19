
#include "crypto/aesEncryptor.h"

namespace butterfly
{

AESEncryptor::AESEncryptor() : CryptoAES()
{

}

std::string AESEncryptor::getAESKey() const
{
    std::string str(reinterpret_cast<const char *>(_aesKey));
    return str;
}

std::string AESEncryptor::getAESIv() const
{
    std::string str(reinterpret_cast<const char *>(_aesIv));
    return str;
}

void AESEncryptor::encryptFile(const std::string &filename)
{
    std::string fileData = butterfly::readBinFile(filename);
    LOG_TRACE(fileData.length() << " bytes to encrypt for file " << filename);

    unsigned char *encryptedFile;
    long encryptedFileLength = CryptoAES::encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    if (encryptedFileLength == -1)
    {
        LOG_TRACE("Encryption failed with file " << filename);
        throw AESEncryptionException("AES Encryption failed with file " + filename);
    }

    LOG_TRACE("Encrypted successfully" << encryptedFileLength << " bytes from file " << filename);

    std::string outFile = filename + butterfly::encryptedFileEnding;
    butterfly::writeBinFile(outFile, reinterpret_cast<const char *>(encryptedFile), encryptedFileLength);
    LOG_INFO("Encrypted file written to " << outFile);

}

void AESEncryptor::encryptFile_old(char *filename)
{
    // Read the file to encrypt
    unsigned char *file;
    int fileLength = CryptoAES::readFile(filename, &file);
    //std::string data = butterfly::readFile(filename);
    printf("%d bytes to be encrypted\n", (int)fileLength);

    // Encrypt the file
    //unsigned char *encryptedFile;
    unsigned char *encryptedFile;
    int encryptedFileLength = static_cast<int>(CryptoAES::encrypt(file, static_cast<size_t>(fileLength), &encryptedFile));

    if(encryptedFileLength == -1) {
        fprintf(stderr, "Encryption failed\n");
        exit(1);
    }
    printf("%d bytes encrypted\n", encryptedFileLength);

    // Append .enc to the filename
    char *encryptedFilename = CryptoAES::appendToString(filename, (char*)".enc");

    // Write the encrypted file to its own file
    //std::string d = "dec";

    CryptoAES::writeFile(encryptedFilename, encryptedFile, static_cast<size_t>(encryptedFileLength));
    printf("Encrypted file written to \"%s\"\n", encryptedFilename);

    free(file);
}

} // namespace butterfly
