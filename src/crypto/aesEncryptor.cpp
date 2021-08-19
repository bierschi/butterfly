
#include "crypto/aesEncryptor.h"

namespace butterfly
{

namespace aes
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
    size_t encryptedFileLength = CryptoAES::encrypt(reinterpret_cast<const unsigned char *>(fileData.c_str()), fileData.length(), &encryptedFile);

    if (encryptedFileLength == 0)
    {
        LOG_TRACE("AES Encryption failed with file " << filename);
        throw AESEncryptionException("AES Encryption failed with file " + filename);
    }

    LOG_TRACE("Encrypted successfully " << encryptedFileLength << " bytes from file " << filename);

    std::string outFile = filename + butterfly::encryptedFileEnding;
    butterfly::writeBinFile(outFile, reinterpret_cast<const char *>(encryptedFile), static_cast<long>(encryptedFileLength));
    LOG_INFO("Encrypted file written to " << outFile);

}

} // namespace aes

} // namespace butterfly
