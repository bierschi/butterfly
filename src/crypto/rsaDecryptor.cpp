
#include "crypto/rsaDecryptor.h"

namespace butterfly
{

namespace rsa
{

RSADecryptor::RSADecryptor(const std::string &key) : CryptoRSA(key), _cPrivateRSAKeyLength(0), _aesKeyLength(0), _aesIvLength(0)
{
    #ifdef LOGGING
    LOG_TRACE("Create class RSADecryptor from rsa key string with key size of " << CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()))
    #endif
}

bool RSADecryptor::validateStringLengthForRSA(const std::string &msg, const int &keysize)
{
    #ifdef LOGGING
    LOG_TRACE("Validating message length " << msg.length() << " with key size " << keysize);
    #endif
    if (static_cast<int>(msg.length()) > keysize)
    {
        return false;
    }
    return true;
}

void RSADecryptor::readRSAFileFromSystem(const RSAKEY_TYPE &rsakeysType, std::string &encKey, std::string &iv)
{

    std::string rsaek;
    if ( butterfly::existsFile(butterfly::params::RSA_EKIV_FILENAME) )
    {
        rsaek = butterfly::readBinFile(butterfly::params::RSA_EKIV_FILENAME);
    } else
    {
        throw FileNotFoundException("File " + butterfly::params::RSA_EKIV_FILENAME + " not found");
    }

    #ifdef LOGGING
    LOG_TRACE("File " << butterfly::params::RSA_EKIV_FILENAME << " has a length of " << rsaek.length() << " bytes");
    #endif

    //       cPKey       AESKey
    // |0 - 1721 | 16 | 256 | 16 | = 2009 Bytes
    if ( rsakeysType == butterfly::RSAKEY_TYPE::CPRIVATE_RSA )
    {
        // 1721 Bytes
        _cPrivateRSAKeyLength = static_cast<unsigned long>(CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()));

        encKey = rsaek.substr(0, _cPrivateRSAKeyLength );
        iv = rsaek.substr(_cPrivateRSAKeyLength, EVP_MAX_IV_LENGTH);

    } else if ( rsakeysType == butterfly::RSAKEY_TYPE::AESKEY )
    {
        // 256 Bytes
        _aesKeyLength = static_cast<unsigned long>(CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()));

        if (rsaek.length() > _aesKeyLength)
        {
            encKey = rsaek.substr(rsaek.length() - _aesKeyLength - EVP_MAX_IV_LENGTH, _aesKeyLength);
            iv = rsaek.substr(rsaek.length() - EVP_MAX_IV_LENGTH, EVP_MAX_IV_LENGTH);
        } else
        {
            #ifdef LOGGING
            LOG_ERROR("RSAEK with size of " << rsaek.length() << " is smaller than AESKeyLength of " << _aesKeyLength);
            #endif
        }

    } else
    {
        #ifdef LOGGING
        LOG_ERROR("RSAKEY_TYPE Number " + std::to_string(rsakeysType) + " is not implemented!");
        #endif
        std::cerr << "RSAKEY_TYPE Number " + std::to_string(rsakeysType) + " is not implemented!" << std::endl;
    }
    /*else
    {
        // 256 Bytes
        _aesIvLength = static_cast<unsigned long>(CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()));

        encKey = rsaek.substr(_cPrivateRSAKeyLength + EVP_MAX_IV_LENGTH + _aesKeyLength + EVP_MAX_IV_LENGTH,  _aesIvLength);
        iv = rsaek.substr(_cPrivateRSAKeyLength + _aesKeyLength + _aesIvLength + (EVP_MAX_IV_LENGTH * 2), EVP_MAX_IV_LENGTH);

    }*/

    if ( encKey.empty() )
    {
        #ifdef LOGGING
        LOG_ERROR("encKey is empty for RSAKEY_TYPE " << rsakeysType)
        #endif
        throw RSADecryptionException("encKey is empty for RSAKEY_TYPE " + std::to_string(rsakeysType));
    }

    if ( iv.empty() )
    {
        #ifdef LOGGING
        LOG_ERROR("iv is empty for RSAKEY_TYPE " << rsakeysType)
        #endif
        throw RSADecryptionException("iv is empty for RSAKEY_TYPE " + std::to_string(rsakeysType));
    }
}

std::string RSADecryptor::readEncMSGFromFile(const std::string &filepath)
{
    if ( butterfly::existsFile(filepath) )
    {
        std::string binFile = butterfly::readBinFile(filepath);
        if ( binFile.empty() )
        {
            #ifdef LOGGING
            LOG_ERROR("Content of binary file " + filepath + " is empty!")
            #endif
            throw RSADecryptionException("Content of binary file " + filepath + " is empty!");
        } else
        {
            return binFile;
        }
    } else
    {
        #ifdef LOGGING
        LOG_ERROR("Binary File " << filepath << " does not exists!")
        #endif
        throw FileNotFoundException("Binary File " + filepath + " does not exists!");
    }

}

int RSADecryptor::decrypt(EVP_PKEY *pkey, const std::string &encMSG, std::string &decMSG)
{

    // First check the message size
    if ( encMSG.empty() )
    {
        #ifdef LOGGING
        LOG_ERROR("Empty messages can not be decrypted!")
        #endif
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // Validate the string length with block size length
    if ( !validateStringLengthForRSA(encMSG, keysize) )
    {
        #ifdef LOGGING
        LOG_ERROR("Error on validateStringLengthForRSA()!")
        #endif
        throw RSADecryptionException("Error on validateStringLengthForRSA()!");
    }

    // Decrypt the message
    unsigned char plaintextKey[keysize];
    int decLen = CryptoRSA::decrypt(pkey, const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(encMSG.c_str())), static_cast<size_t >(keysize), plaintextKey);

    if (decLen == -1)
    {
        #ifdef LOGGING
        LOG_ERROR("Error at decrypting the message with RSA!")
        #endif
        throw RSADecryptionException("Error at decrypting the message with RSA!");
    }

    _decryptedMessage.resize(static_cast<size_t>(decLen));
    std::copy(plaintextKey, plaintextKey + decLen, _decryptedMessage.begin());

    std::string str(reinterpret_cast<const char *>(plaintextKey), static_cast<unsigned long>(decLen));

    decMSG = str;

    return decLen;
}

int RSADecryptor::decryptEVP(EVP_PKEY *pkey, const std::string &encMSG, std::string &decMSG, const RSAKEY_TYPE &type)
{

    // First check the message size
    if ( encMSG.empty() )
    {
        #ifdef LOGGING
        LOG_ERROR("Empty messages can not be decrypted!")
        #endif
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    std::string encKey, iv;
    readRSAFileFromSystem(type, encKey, iv);

    // Decrypt the encrypted Message
    char *decryptedMessage = nullptr;
    int decLen = CryptoRSA::decryptEVP(pkey, (unsigned char *) encMSG.c_str(), encMSG.length(), (unsigned char *) encKey.c_str(), (unsigned char *) iv.c_str(), (unsigned char**)&decryptedMessage);

    if (decLen == -1)
    {
        #ifdef LOGGING
        LOG_ERROR("Error at decrypting the message with RSA!")
        #endif
        throw RSADecryptionException("Error at decrypting the message with RSA!");
    }

    _decryptedMessage.resize(static_cast<size_t>(decLen));
    std::copy(decryptedMessage, decryptedMessage + decLen, _decryptedMessage.begin());

    std::string str(reinterpret_cast<const char *>(decryptedMessage), static_cast<unsigned long>(decLen));

    decMSG = str;

    return decLen;
}

} // namespace rsa

} // namespace butterfly
