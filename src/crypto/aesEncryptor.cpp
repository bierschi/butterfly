
#include "crypto/aesEncryptor.h"

namespace butterfly
{

namespace aes
{

AESEncryptor::AESEncryptor() : CryptoAES()
{
    LOG_TRACE("Create class AESEncryptor");
}

void AESEncryptor::encryptFile(const std::string &filename)
{

    std::string fileData = butterfly::readBinFile(filename);
    double fileSize = butterfly::getFileSize(filename);
    LOG_TRACE("Encrypting file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");

    unsigned char *encryptedFile;
    size_t encryptedFileLength = CryptoAES::encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    if (encryptedFileLength == 0)
    {
        LOG_TRACE("AES Encryption failed with file " << filename);
        throw AESEncryptionException("AES Encryption failed with file " + filename);
    }

    std::string outFile = filename + butterfly::ENC_BFLY_FILE_ENDING;
    butterfly::writeBinFile(outFile, reinterpret_cast<const char *>(encryptedFile), static_cast<long>(encryptedFileLength));
    LOG_INFO("Encrypted successfully file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    std::cout << "Encrypted successfully file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;

    if ( !butterfly::removeFile(filename) )
    {
        throw AESEncryptionException("Failed to remove file " + filename);
    }

}

} // namespace aes

} // namespace butterfly
