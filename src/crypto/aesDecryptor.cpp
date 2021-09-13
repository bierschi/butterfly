
#include "crypto/aesDecryptor.h"

namespace butterfly
{

namespace aes
{

AESDecryptor::AESDecryptor() : CryptoAES()
{
    LOG_TRACE("Create class AESDecryptor");
}

void AESDecryptor::decryptFile(const std::string &bflyFileName)
{

    std::string fileData = butterfly::readBinFile(bflyFileName);
    double fileSize = butterfly::getFileSize(bflyFileName);
    LOG_TRACE("Decrypting file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");


    unsigned char *decryptedFile;
    size_t decryptedFileLength = CryptoAES::decrypt((unsigned char *) fileData.c_str(), fileData.length(), &decryptedFile);

    if (decryptedFileLength == 0)
    {
        LOG_TRACE("AES Decryption failed with file " << bflyFileName);
        throw AESDecryptionException("AES Decryption failed with file " + bflyFileName);
    }

    butterfly::writeBinFile(bflyFileName, reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));
    LOG_INFO("Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    std::cout << "Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;

    if ( !butterfly::removeFileExtension(const_cast<std::string &>(bflyFileName), butterfly::ENC_BFLY_FILE_ENDING) )
    {
        throw AESDecryptionException("Failed to remove bfly extension from file " + bflyFileName);
    }

}

} // namespace aes

} // namespace butterfly
