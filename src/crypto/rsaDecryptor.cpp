
#include "crypto/rsaDecryptor.h"

namespace butterfly
{

namespace rsa
{

unsigned long RSADecryptor::cPrivateRSAKeyLength = 0, RSADecryptor::AESKEYLength = 0, RSADecryptor::AESIVLength = 0;

RSADecryptor::RSADecryptor(const std::string &key) : CryptoRSA(key)
{
    LOG_TRACE("Create class RSADecryptor from rsa key string with key size of " << CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()))
}

bool RSADecryptor::validateStringLengthForRSA(const std::string &msg, const int &keysize)
{
    LOG_TRACE("Validating message length " << msg.length() << " with key size " << keysize);

    if (static_cast<int>(msg.length()) > keysize)
    {
        return false;
    }
    return true;
}

void RSADecryptor::readRSAFileFromSystem(const RSAKEY_TYPE &rsakeysType, std::string &encKey, std::string &iv)
{

    std::string rsaek;
    rsaek = butterfly::readBinFile(butterfly::RSA_EKIV_FILENAME);

    //       cPKey       AESKey      AESIV
    // |0 - 1721 | 16 | 256 | 16 | 256 | 16 |
    if ( rsakeysType == butterfly::RSAKEY_TYPE::CPRIVATE_RSA )
    {
        // 1721 Bytes
        RSADecryptor::cPrivateRSAKeyLength = static_cast<unsigned long>(CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()));

        encKey = rsaek.substr(0, RSADecryptor::cPrivateRSAKeyLength );
        iv = rsaek.substr(RSADecryptor::cPrivateRSAKeyLength, EVP_MAX_IV_LENGTH);

    } else if ( rsakeysType == butterfly::RSAKEY_TYPE::AESKEY )
    {
        // 256 Bytes
        RSADecryptor::AESKEYLength = static_cast<unsigned long>(CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()));

        encKey = rsaek.substr(RSADecryptor::cPrivateRSAKeyLength + EVP_MAX_IV_LENGTH, RSADecryptor::AESKEYLength);
        iv = rsaek.substr(RSADecryptor::cPrivateRSAKeyLength + EVP_MAX_IV_LENGTH + RSADecryptor::AESKEYLength, EVP_MAX_IV_LENGTH);

    } /*else
    {
        // 256 Bytes
        RSADecryptor::AESIVLength = static_cast<unsigned long>(CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()));

        encKey = rsaek.substr(RSADecryptor::cPrivateRSAKeyLength + EVP_MAX_IV_LENGTH + RSADecryptor::AESKEYLength + EVP_MAX_IV_LENGTH,  RSADecryptor::AESIVLength);
        iv = rsaek.substr(RSADecryptor::cPrivateRSAKeyLength + RSADecryptor::AESKEYLength + RSADecryptor::AESIVLength + (EVP_MAX_IV_LENGTH * 2), EVP_MAX_IV_LENGTH);

    }*/

    if ( encKey.empty() )
    {
        LOG_ERROR("encKey is empty for RSAKEY_TYPE " << rsakeysType)
        throw RSADecryptionException("encKey is empty for RSAKEY_TYPE " + std::to_string(rsakeysType));
    }

    if ( iv.empty() )
    {
        LOG_ERROR("iv is empty for RSAKEY_TYPE " << rsakeysType)
        throw RSADecryptionException("iv is empty for RSAKEY_TYPE " + std::to_string(rsakeysType));
    }
}

std::string RSADecryptor::readEncMSGFromFile(const std::string &filepath)
{

    std::string binFile = butterfly::readBinFile(filepath);
    if ( binFile.empty() )
    {
        LOG_ERROR("Content of binary file " + filepath + " is empty!")
        throw RSADecryptionException("Content of binary file " + filepath + " is empty!");
    } else
    {
        return binFile;
    }

}

void RSADecryptor::decrypt(EVP_PKEY *pkey, const std::string &encMSG, std::string &decMSG)
{

    // First check the message size
    if ( encMSG.empty() )
    {
        LOG_ERROR("Empty messages can not be decrypted!")
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // Validate the string length with block size length
    if ( !validateStringLengthForRSA(encMSG, keysize) )
    {
        LOG_ERROR("Error on validateStringLengthForRSA()!")
        throw RSADecryptionException("Error on validateStringLengthForRSA()!");
    }

    // Decrypt the message
    unsigned char plaintextKey[keysize];
    CryptoRSA::decrypt(pkey, const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(encMSG.c_str())), static_cast<size_t >(keysize), plaintextKey);

    _decryptedMessage = reinterpret_cast<char *>(plaintextKey);
    decMSG = reinterpret_cast<char *>(plaintextKey);

}

void RSADecryptor::decryptEVP(EVP_PKEY *pkey, const std::string &encMSG, std::string &decMSG, const RSAKEY_TYPE &type)
{

    // First check the message size
    if ( encMSG.empty() )
    {
        LOG_ERROR("Empty messages can not be decrypted!")
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    std::string encKey, iv;
    readRSAFileFromSystem(type, encKey, iv);

    // Decrypt the encrypted Message
    char *decryptedMessage = nullptr;
    size_t decLen = CryptoRSA::decryptEVP(pkey, (unsigned char *) encMSG.c_str(), encMSG.length(), (unsigned char *) encKey.c_str(), (unsigned char *) iv.c_str(), (unsigned char**)&decryptedMessage);

    _decryptedMessage.resize(static_cast<size_t>(decLen));
    std::copy(decryptedMessage, decryptedMessage + decLen, _decryptedMessage.begin());

    std::string str(reinterpret_cast<const char *>(decryptedMessage), decLen);

    decMSG = str;

}

} // namespace rsa

} // namespace butterfly
