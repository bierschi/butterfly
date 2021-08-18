
#include "crypto/aesEncryptor.h"

namespace butterfly
{

AESEncryptor::AESEncryptor() : CryptoAES()
{

}

void AESEncryptor::encryptFile(char *filename)
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
