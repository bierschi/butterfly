
#include "crypto/aesEncryptor.h"

namespace butterfly
{

namespace aes
{

AESEncryptor::AESEncryptor() : CryptoAES()
{
    LOG_TRACE("Create class AESEncryptor");
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
    LOG_TRACE(std::fixed << std::setprecision(3) << (fileData.length() / (1024 * 1024)) << " Mbytes to encrypt for file " << filename);

    unsigned char *encryptedFile;
    size_t encryptedFileLength = CryptoAES::encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    if (encryptedFileLength == 0)
    {
        LOG_TRACE("AES Encryption failed with file " << filename);
        throw AESEncryptionException("AES Encryption failed with file " + filename);
    }

    std::string outFile = filename + butterfly::ENCRYPTED_FILE_ENDING;
    butterfly::writeBinFile(outFile, reinterpret_cast<const char *>(encryptedFile), static_cast<long>(encryptedFileLength));
    LOG_INFO("Encrypted successfully " << std::fixed << std::setprecision(3) << (encryptedFileLength / (1024 * 1024)) << " Mbytes from file " << filename);

    if ( !butterfly::removeFile(filename) )
    {
        throw AESEncryptionException("Failed to remove file " + filename);
    }

}

} // namespace aes

} // namespace butterfly
