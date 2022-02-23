
#include "crypto/aesDecryptor.h"

namespace butterfly
{

namespace aes
{

AESDecryptor::AESDecryptor() : CryptoAES()
{
    #ifdef LOGGING
    LOG_TRACE("Create class AESDecryptor");
    #endif
}

void AESDecryptor::decryptFile(const std::string &bflyFileName)
{

    std::string fileData = butterfly::readBinFile(bflyFileName);

    if ( fileData.empty() )
    {
        #ifdef LOGGING
        LOG_TRACE("Empty Data from file " + bflyFileName);
        #endif
        throw AESDecryptionException("Empty Data from file " + bflyFileName);
    }

    double fileSize = butterfly::getFileSize(bflyFileName);
    #ifdef LOGGING
    LOG_TRACE("Decrypting file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    #endif

    unsigned char *decryptedFile;
    size_t decryptedFileLength = CryptoAES::decrypt((unsigned char *) fileData.c_str(), fileData.length(), &decryptedFile);

    if (decryptedFileLength == 0)
    {
        #ifdef LOGGING
        LOG_TRACE("AES Decryption failed with file " << bflyFileName);
        #endif
        throw AESDecryptionException("AES Decryption failed with file " + bflyFileName);
    }

    butterfly::writeBinFile(bflyFileName, reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));
    #ifdef LOGGING
    if ( Logger::isConfigFileAvailable() )
    {
        LOG_INFO("Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    } else
    {
        std::cout << "Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;
    }
    #else
    std::cout << "Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;
    #endif

    if ( !butterfly::removeFileExtension(const_cast<std::string &>(bflyFileName), butterfly::params::ENC_BFLY_FILE_ENDING) )
    {
        #ifdef LOGGING
        LOG_TRACE("Failed to remove bfly extension from file " + bflyFileName);
        #endif
        throw AESDecryptionException("Failed to remove bfly extension from file " + bflyFileName);
    }

}

} // namespace aes

} // namespace butterfly
