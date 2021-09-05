
#include "crypto/rsaDecryptor.h"

namespace butterfly
{

namespace rsa
{

RSADecryptor::RSADecryptor() : CryptoRSA(2048)
{
    LOG_TRACE("Create class RSADecryptor as default constructor")
}

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

std::string RSADecryptor::getBinKeyFileContents(const std::string &filepath)
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

void RSADecryptor::decrypt(EVP_PKEY *pkey, const std::string &msg)
{

    // first check the message size
    if ( msg.empty() )
    {
        LOG_ERROR("Empty messages can not be decrypted!")
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // validate the string length with block size length
    if ( !validateStringLengthForRSA(msg, keysize) )
    {
        LOG_ERROR("Error on validateStringLengthForRSA()!")
        throw RSADecryptionException("Error on validateStringLengthForRSA()!");
    }

    unsigned char plaintextKey[keysize];
    CryptoRSA::decrypt(pkey, const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(msg.c_str())), static_cast<size_t >(keysize), plaintextKey);

    _decryptedMessage = reinterpret_cast<char *>(plaintextKey);

}

void RSADecryptor::decryptEVP(EVP_PKEY *pkey, const std::string &msg)
{

    // first check the message size
    if ( msg.empty() )
    {
        LOG_ERROR("Empty messages can not be decrypted!")
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    //int keysize = CryptoRSAA::getEvpPkeySize(pkey);

    std::string encKey = butterfly::readBinFile("encryptedKey.txt");
    std::string iv2 = butterfly::readBinFile("iv.txt");

    char *decryptedMessage = nullptr;
    CryptoRSA::decryptEVP(pkey, (unsigned char *) msg.c_str(), msg.length(), (unsigned char *) encKey.c_str(), (unsigned char *) iv2.c_str(), (unsigned char**)&decryptedMessage);

    _decryptedMessage = reinterpret_cast<char *>(decryptedMessage);

}

} // namespace rsa

} // namespace butterfly
