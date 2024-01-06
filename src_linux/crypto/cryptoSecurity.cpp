
#include "crypto/cryptoSecurity.h"

namespace butterfly
{

namespace hybrid
{

void CryptoSecurity::saveUnencryptedAESKeyPair(const std::string &aesKeyPair)
{
    // 32 Bytes AESKey + 16 Bytes IV
    if ( !butterfly::writeBinFile(butterfly::params::UNENC_AESKEY_FILENAME, aesKeyPair.c_str(), static_cast<long>(aesKeyPair.length())) )
    {
        #ifdef LOGGING
        LOG_ERROR("Could not save the unencrypted AESKeyPair File to Filesystem!");
        #else
        std::cerr << "Could not save the unencrypted AESKeyPair File to Filesystem!" << std::endl;
        #endif
    }

}

bool CryptoSecurity::areEncryptionFilesAvailable()
{
    if ( butterfly::existsFile(butterfly::params::ENC_CPRIVATERSA_FILENAME) && butterfly::existsFile(butterfly::params::ENC_AESKEY_FILENAME) && butterfly::existsFile(butterfly::params::RSA_EKIV_FILENAME) )
    {
        return true;
    }
    return false;
}

void CryptoSecurity::removeDecryptedFiles()
{

    butterfly::removeFile(butterfly::params::ENC_CPRIVATERSA_FILENAME);
    butterfly::removeFile(butterfly::params::ENC_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::params::RSA_EKIV_FILENAME);

}

bool CryptoSecurity::getAESKeyPairFromUnencryptedFile(std::string &aeskeypair)
{
    if ( butterfly::existsFile(butterfly::params::UNENC_AESKEY_FILENAME) )
    {
        aeskeypair = butterfly::readBinFile(butterfly::params::UNENC_AESKEY_FILENAME);

        if ( !aeskeypair.empty() )
        {
            return true;
        } else
        {
            return false;
        }
    } else
    {
        return false;
    }
}

} // namespace hybrid

} //namespace butterfly
