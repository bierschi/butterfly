
#include "crypto/aesDecryptor.h"

namespace butterfly
{

namespace aes
{

AESDecryptor::AESDecryptor() : CryptoAES()
{
    LOG_TRACE("Create class AESDecryptor");
}

void AESDecryptor::setAESKey(const std::string &aesKey)
{
    _aesKey = reinterpret_cast<unsigned char*>(const_cast<char*>(aesKey.c_str()));
}

void AESDecryptor::setAESIv(const std::string &aesIv)
{
    _aesIv = reinterpret_cast<unsigned char*>(const_cast<char*>(aesIv.c_str()));
}

void AESDecryptor::decryptFile(const std::string &filename)
{

    std::string bflyFileName = filename + butterfly::ENC_BFLY_FILE_ENDING;

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

    butterfly::writeBinFile(filename, reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));
    LOG_INFO("Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB");
    std::cout << "Decrypted successfully file " << bflyFileName << " with size of " << std::fixed << std::setprecision(2) << fileSize << " MB" << std::endl;

    if ( !butterfly::removeFile(bflyFileName) )
    {
        throw AESDecryptionException("Failed to remove file " + bflyFileName);
    }

}

} // namespace aes

} // namespace butterfly
