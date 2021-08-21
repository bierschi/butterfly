
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

    std::string fileData = butterfly::readBinFile(filename + butterfly::ENCRYPTED_FILE_ENDING);
    LOG_TRACE(fileData.length() << " bytes to decrypt for file " << filename + butterfly::ENCRYPTED_FILE_ENDING);

    unsigned char *decryptedFile;
    size_t decryptedFileLength = CryptoAES::decrypt((unsigned char *) fileData.c_str(), fileData.length(), &decryptedFile);

    if (decryptedFileLength == 0)
    {
        LOG_TRACE("AES Decryption failed with file " << filename);
        throw AESDecryptionException("AES Decryption failed with file " + filename + butterfly::ENCRYPTED_FILE_ENDING);
    }

    LOG_TRACE("Decrypted successfully " << decryptedFileLength << " bytes from file " << filename + butterfly::ENCRYPTED_FILE_ENDING);

    //std::string outFile = filename + ".dec";
    butterfly::writeBinFile(filename, reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));
    LOG_INFO("Decrypted file written to " << filename);

    if ( !butterfly::removeFile(filename + butterfly::ENCRYPTED_FILE_ENDING) )
    {
        throw AESDecryptionException("Failed to remove file " + filename + butterfly::ENCRYPTED_FILE_ENDING);
    }

}

} // namespace aes

} // namespace butterfly
