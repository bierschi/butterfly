
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

    std::string fileData = butterfly::readBinFile(filename + butterfly::ENC_BFLY_FILE_ENDING);
    LOG_TRACE(std::setprecision(3) << (fileData.length()/(1024 * 1024)) << " Mbytes to decrypt for file " << filename + butterfly::ENC_BFLY_FILE_ENDING);

    unsigned char *decryptedFile;
    size_t decryptedFileLength = CryptoAES::decrypt((unsigned char *) fileData.c_str(), fileData.length(), &decryptedFile);

    if (decryptedFileLength == 0)
    {
        LOG_TRACE("AES Decryption failed with file " << filename);
        throw AESDecryptionException("AES Decryption failed with file " + filename + butterfly::ENC_BFLY_FILE_ENDING);
    }

    //std::string outFile = filename + ".dec";
    butterfly::writeBinFile(filename, reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));
    LOG_INFO("Decrypted successfully " << std::setprecision(3) << (decryptedFileLength / (1024 * 1024)) << " Mbytes from file " << filename + butterfly::ENC_BFLY_FILE_ENDING);
    std::cout << "Decrypted successfully " << std::setprecision(3) << (decryptedFileLength / (1024 * 1024)) << " Mbytes from file " << filename + butterfly::ENC_BFLY_FILE_ENDING << std::endl;

    if ( !butterfly::removeFile(filename + butterfly::ENC_BFLY_FILE_ENDING) )
    {
        throw AESDecryptionException("Failed to remove file " + filename + butterfly::ENC_BFLY_FILE_ENDING);
    }

}

} // namespace aes

} // namespace butterfly
