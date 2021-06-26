
#include "crypto/rsaDecryptor.h"

namespace butterfly
{

RSADecryptor::RSADecryptor() : CryptoRSA()
{
    LOG_TRACE("Create class RSADecryptor as default constructor")
}

RSADecryptor::RSADecryptor(const std::string &key) : CryptoRSA(key)
{
    LOG_TRACE("Create class RSADecryptor from rsa key string with key size of " << CryptoRSA::getRSAKeySize() * 8)
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

EVP_PKEY *RSADecryptor::getEvpPkeyFromFile(const std::string &filepath)
{

    EVP_PKEY *pkey = nullptr;
    std::ifstream in(filepath, std::ios::in);

    if (in.is_open())
    {

        std::string fLine;
        std::getline(in, fLine);

        if (fLine == "-----BEGIN RSA PRIVATE KEY-----")
        {

            pkey = CryptoRSA::getPkeyFromPrivateKeyFile(filepath);

        } else if (fLine == "-----BEGIN PUBLIC KEY-----")
        {

            pkey = CryptoRSA::getPkeyFromPublicKeyFile(filepath);

        } else
        {
            LOG_ERROR("Unsupported file provided with file header: " << fLine);
        }

    } else
    {
        LOG_ERROR("Failed to open file " << filepath);
    }

    return pkey;
}

std::string RSADecryptor::getBinKeyFileContents(const std::string &filepath)
{

    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    std::string encKey;

    if (in.is_open())
    {
        std::stringstream strStream;
        strStream << in.rdbuf();
        encKey = strStream.str();
        return encKey;
    } else
    {
        LOG_ERROR("Failed to open file " << filepath);
        return encKey;
    }
}

bool RSADecryptor::decrypt(EVP_PKEY *pkey, const std::string &msg)
{

    // first check the message size
    if (msg.empty())
    {
        LOG_ERROR("Can not decrypt message because it is empty!")
        return false;
    }

    int keysize = CryptoRSA::getEvpPkeySize(pkey);

    // validate the string length with block size length
    if (!validateStringLengthForRSA(msg, keysize))
    {
        LOG_ERROR("Encrypted message string to big for RSA key length!")
        return false;
    }

    unsigned char plaintextKey[keysize];

    CryptoRSA::decrypt(pkey, const_cast<unsigned char *>(reinterpret_cast<const unsigned char *>(msg.c_str())),
                       static_cast<size_t >(keysize), plaintextKey);

    _decryptedKey = reinterpret_cast<char *>(plaintextKey);

    return true;
}

} // namespace butterfly
