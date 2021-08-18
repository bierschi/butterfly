
#include <iostream>
#include "crypto/aesDecryptor.h"

namespace butterfly
{

AESDecryptor::AESDecryptor()
{

}


void AESDecryptor::decryptFile(char *filename, char *encryptedFilename)
{
    // Read the encrypted file back
    unsigned char *file;
    size_t fileLength = static_cast<size_t>(CryptoAES::readFile(encryptedFilename, &file));

    // Decrypt the encrypted file
    unsigned char *decryptedFile;
    int decryptedFileLength = static_cast<int>(CryptoAES::decrypt(file, fileLength, &decryptedFile));

    if(decryptedFileLength == -1) {
        fprintf(stderr, "Decryption failed\n");
        exit(1);
    }
    printf("%d bytes decrypted\n", (int)decryptedFileLength);

    // Append .dec to the filename
    char *decryptedFilename = CryptoAES::appendToString(filename, (char*)".dec");

    // Write the decrypted file to its own file
    writeFile(decryptedFilename, decryptedFile, static_cast<size_t>(decryptedFileLength));
    printf("Decrypted file written to \"%s\"\n", decryptedFilename);

    free(decryptedFile);
    free(decryptedFilename);
    free(file);
}

} // namespace butterfly

