
#include "crypto/rsaEncryptor.h"

namespace butterfly
{

namespace rsa
{

RSAEncryptor::RSAEncryptor(int keySize) : CryptoRSA(keySize)
{
    #ifdef LOGGING
    LOG_TRACE("Create class RSAEncryptor with key size of " << keySize)
    #endif
}

RSAEncryptor::RSAEncryptor(const std::string &key) : CryptoRSA(key)
{
    #ifdef LOGGING
    LOG_TRACE("Create class RSAEncryptor from rsa key string with key size of " << CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()))
    #endif
}

bool RSAEncryptor::validateStringLengthForRSA(const std::string &msg, const int &keysize)
{

    int msgLength = static_cast<int>(msg.length());
    int maxBlockSize = (keysize - CryptoRSA::getPaddingSize());

    if (msgLength < maxBlockSize)
    {
        #ifdef LOGGING
        LOG_INFO("Message string " << msg << " with length of " << msgLength
                                   << " bytes is less than RSA block size of max " << maxBlockSize
                                   << " bytes (RSA key size: " << keysize << " - padding size: "
                                   << CryptoRSA::getPaddingSize() << ")");
        #endif
        return true;
    } else
    {
        #ifdef LOGGING
        LOG_ERROR("Message string " << msg << " with length of " << msgLength
                                    << " bytes is greater/equal than RSA block size of max " << maxBlockSize
                                    << " bytes (RSA key size: " << keysize << " - padding size: "
                                    << CryptoRSA::getPaddingSize() << ")");
        #endif
        return false;
    }

}

bool RSAEncryptor::writeRSAFileToSystem()
{

    unsigned char* encryptedKey = CryptoRSA::getRSAEncryptedKey();
    unsigned char* iv = CryptoRSA::getRSAIV();

    if ( butterfly::writeBinFile(butterfly::RSA_EKIV_FILENAME, reinterpret_cast<const char *>(encryptedKey), CryptoRSA::getEvpPkeySize(CryptoRSA::getEvpPkey()), true) )
    {
        if ( butterfly::writeBinFile(butterfly::RSA_EKIV_FILENAME, reinterpret_cast<const char *>(iv), EVP_MAX_IV_LENGTH, true) )
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

void RSAEncryptor::writeEncMSGToFile(const std::string &filename, const std::string &ciphertextMsg, int ciphertextMsgLength)
{

    if ( !butterfly::writeBinFile(filename, ciphertextMsg.c_str(), ciphertextMsgLength) )
    {
        #ifdef LOGGING
        LOG_ERROR("Error at writing to binary file " + filename)
        #endif
        throw RSAEncryptionException("Error at writing to binary file " + filename);
    }

}

int RSAEncryptor::encrypt(EVP_PKEY *pkey, const std::string &msg)
{

    // First check the message size
    if ( msg.empty() )
    {
        #ifdef LOGGING
        LOG_ERROR("Empty messages can not be encrypted")
        #endif
        throw RSAEncryptionException("Empty messages can not be encrypted!");
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // Validate the string length with block size length
    if ( !validateStringLengthForRSA(msg, keysize) )
    {
        #ifdef LOGGING
        LOG_ERROR("Error on validateStringLengthForRSA()!")
        #endif
        throw RSAEncryptionException("Error on validateStringLengthForRSA()!");
    }

    // Encrypt the message
    unsigned char ciphertextKey[keysize];
    int encLen = CryptoRSA::encrypt(pkey, (unsigned char *) msg.c_str(), msg.size(), ciphertextKey);

    if (encLen == -1)
    {
        #ifdef LOGGING
        LOG_ERROR("Error at encrypting the message with RSA!")
        #endif
        throw RSAEncryptionException("Error at encrypting the message with RSA!");
    }

    _encryptedMessage.resize(static_cast<size_t>(encLen));
    std::copy(ciphertextKey, ciphertextKey + encLen, _encryptedMessage.begin());

    return encLen;
}

int RSAEncryptor::encryptEVP(EVP_PKEY *pkey, const std::string &decMSG)
{
    // First check the message size
    if ( decMSG.empty() )
    {
        #ifdef LOGGING
        LOG_ERROR("Empty messages can not be encrypted!")
        #endif
        throw RSAEncryptionException("Empty messages can not be encrypted!");
    }

    // Encrypt the message
    unsigned char *encryptedMessage = nullptr;
    //int encLen = CryptoRSA::encryptEVP(pkey, reinterpret_cast<const unsigned char *>(decMSG.c_str()), decMSG.size() + 1, &encryptedMessage);
    int encLen = CryptoRSA::encryptEVP(pkey, reinterpret_cast<const unsigned char *>(decMSG.c_str()), decMSG.size(), &encryptedMessage);

    if (encLen == -1)
    {
        #ifdef LOGGING
        LOG_ERROR("Error at encrypting the message with RSA!")
        #endif
        throw RSAEncryptionException("Error at encrypting the message with RSA!");
    }

    _encryptedMessage.resize(static_cast<unsigned long>(encLen));
    std::copy(encryptedMessage, encryptedMessage + encLen, _encryptedMessage.begin());

    // Write RSA File to System
    if ( !writeRSAFileToSystem() )
    {
        #ifdef LOGGING
        LOG_ERROR("Error at writing RSA file" + butterfly::RSA_EKIV_FILENAME + " to System");
        #endif
        throw RSAEncryptionException("Error at writing RSA file " + butterfly::RSA_EKIV_FILENAME + " to System");
    }

    return encLen;
}

} // namespace rsa

} // namespace butterfly
