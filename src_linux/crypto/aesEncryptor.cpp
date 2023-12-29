
#include "crypto/aesEncryptor.h"

namespace butterfly
{

namespace aes
{

AESEncryptor::AESEncryptor() : CryptoAES()
{
    #ifdef LOGGING
    LOG_TRACE("Create class AESEncryptor");
    #endif
}

void AESEncryptor::encryptFile(const std::string &filename)
{

    std::string fileData = butterfly::readBinFile(filename);

    if ( fileData.empty() )
    {
        #ifdef LOGGING
        LOG_TRACE("Empty Data from file " + filename);
        #endif
        throw AESEncryptionException("Empty Data from file " + filename);
    }

    double fileSize = butterfly::getFileSize(filename);
    #ifdef LOGGING
    LOG_TRACE("Encrypting file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    #endif
    unsigned char *encryptedFile;
    size_t encryptedFileLength = CryptoAES::encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    if (encryptedFileLength == 0)
    {
        #ifdef LOGGING
        LOG_TRACE("AES Encryption failed with file " << filename);
        #endif
        throw AESEncryptionException("AES Encryption failed with file " + filename);
    }

    if ( !butterfly::writeBinFile(filename, reinterpret_cast<const char *>(encryptedFile), static_cast<long>(encryptedFileLength)) )
    {
        #ifdef LOGGING
        LOG_TRACE("Failed to write binary content to file " + filename);
        #endif
        throw AESEncryptionException("Failed to write binary content to file " + filename);
    }

    #ifdef LOGGING
    if ( Logger::isConfigFileAvailable() )
    {
        LOG_INFO("Encrypted successfully file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    } else
    {
        std::cout << "Encrypted successfully file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;
    }
    #else
    std::cout << "Encrypted successfully file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;
    #endif

    if ( !butterfly::appendFileExtension(filename, butterfly::params::ENC_BFLY_FILE_ENDING) )
    {
        #ifdef LOGGING
        LOG_TRACE("Failed to append bfly extension to file " + filename);
        #endif
        throw AESEncryptionException("Failed to append bfly extension to file " + filename);
    }

}

void AESEncryptor::encryptFile2(const std::string &filename)
{

    std::string tmpFilename = filename;

    double fileSize = butterfly::getFileSize(filename);
    #ifdef LOGGING
    LOG_TRACE("Encrypting file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    #endif

    std::ifstream inFile(filename, std::ios::binary | std::ios::in);

    std::ofstream outFile(filename + butterfly::params::ENC_BFLY_FILE_ENDING, std::ios::binary | std::ios::out);

    size_t encryptedFileLength = CryptoAES::encrypt(inFile, outFile);

    if (encryptedFileLength == 0)
    {
        #ifdef LOGGING
        LOG_TRACE("AES Encryption failed with file " << filename);
        #endif
        throw AESEncryptionException("AES Encryption failed with file " + filename);
    }

    #ifdef LOGGING
    if ( Logger::isConfigFileAvailable() )
    {
        LOG_INFO("Encrypted successfully file " << tmpFilename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    } else
    {
        std::cout << "Encrypted successfully file " << tmpFilename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;
    }
    #else
    std::cout << "Encrypted successfully file " << filename << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;
    #endif


}

} // namespace aes

} // namespace butterfly
