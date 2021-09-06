
#include "crypto/rsaDecryptor.h"

namespace butterfly
{

namespace rsa
{

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

void RSADecryptor::readRSAFilesFromSystem(const std::string &type, std::string &encKey, std::string &iv)
{
    std::string rsaek, rsaiv;
    if ( type == butterfly::ENC_CPRIVATERSA_FILENAME )
    {
        rsaek = butterfly::RSA_ENCKEY_CPKEY_FILENAME;
        rsaiv = butterfly::RSA_IV_CPKEY_FILENAME;

    } else if ( type == ENC_AESKEY_FILENAME)
    {
        rsaek = butterfly::RSA_ENCKEY_AESKEY_FILENAME;
        rsaiv = butterfly::RSA_IV_AESKEY_FILENAME;

    } else {
        rsaek = butterfly::RSA_ENCKEY_AESIV_FILENAME;
        rsaiv = butterfly::RSA_IV_AESIV_FILENAME;
    }

    encKey = butterfly::readBinFile(rsaek);
    iv = butterfly::readBinFile(rsaiv);

    if ( encKey.empty() )
    {
        LOG_ERROR(rsaek << " is empty!")
        throw RSADecryptionException(rsaek + " is empty!");
    }

    if ( iv.empty() )
    {
        LOG_ERROR(rsaiv << " is empty!")
        throw RSADecryptionException(rsaiv + " is empty!");
    }
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

    // First check the message size
    if ( msg.empty() )
    {
        LOG_ERROR("Empty messages can not be decrypted!")
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // Validate the string length with block size length
    if ( !validateStringLengthForRSA(msg, keysize) )
    {
        LOG_ERROR("Error on validateStringLengthForRSA()!")
        throw RSADecryptionException("Error on validateStringLengthForRSA()!");
    }

    // Decrypt the message
    unsigned char plaintextKey[keysize];
    CryptoRSA::decrypt(pkey, const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(msg.c_str())), static_cast<size_t >(keysize), plaintextKey);

    _decryptedMessage = reinterpret_cast<char *>(plaintextKey);

}

void RSADecryptor::decryptEVP(EVP_PKEY *pkey, const std::string &msg, const std::string &type)
{

    // First check the message size
    if ( msg.empty() )
    {
        LOG_ERROR("Empty messages can not be decrypted!")
        throw RSADecryptionException("Empty messages can not be decrypted!");
    }

    std::string encKey, iv;
    readRSAFilesFromSystem(type, encKey, iv);

    // Decrypt the Message
    char *decryptedMessage = nullptr;
    CryptoRSA::decryptEVP(pkey, (unsigned char *) msg.c_str(), msg.length(), (unsigned char *) encKey.c_str(), (unsigned char *) iv.c_str(), (unsigned char**)&decryptedMessage);

    _decryptedMessage = reinterpret_cast<char *>(decryptedMessage);

}

} // namespace rsa

} // namespace butterfly
