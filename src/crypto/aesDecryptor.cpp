
#include "crypto/aesDecryptor.h"

namespace butterfly
{

AESDecryptor::AESDecryptor() : CryptoAES()
{

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

    std::string fileData = butterfly::readBinFile(filename);
    LOG_TRACE(fileData.length() << " bytes to decrypt for file " << filename);

    unsigned char *decryptedFile;
    size_t decryptedFileLength = CryptoAES::decrypt((unsigned char *) fileData.c_str(), fileData.length(), &decryptedFile);

    if (decryptedFileLength == 0)
    {
        LOG_TRACE("AES Decryption failed with file " << filename);
        throw AESDecryptionException("AES Decryption failed with file " + filename);
    }

    LOG_TRACE("Decrypted successfully " << decryptedFileLength << " bytes from file " << filename);

    std::string outFile = filename + ".dec";
    butterfly::writeBinFile(outFile, reinterpret_cast<const char *>(decryptedFile), static_cast<long>(decryptedFileLength));
    LOG_INFO("Decrypted file written to " << outFile);

}

} // namespace butterfly

