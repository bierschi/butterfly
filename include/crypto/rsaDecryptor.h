
#ifndef BUTTERFLY_RSADECRYPTOR_H
#define BUTTERFLY_RSADECRYPTOR_H

#include "rsa.h"

namespace butterfly {

/**
 * Class RSADecryptor to provide methods for simple rsa decryption
 */
class RSADecryptor : public CryptoRSA {

private:
    std::string _decryptedKey;

    /**
     * Validates the length of given string with the RSA key size
     */
    int validateStringLengthForRSA(const std::string &msg, const int &keysize);

public:

    /**
     * Constructor RSADecryptor
     */
    RSADecryptor();

    /**
     * Constructor RSADecryptor to init rsa key from key string or file
     *
     * @param key: key string or filepath to key
     */
    RSADecryptor(const std::string &key);

    /**
     * Destructor RSADecryptor
     */
    ~RSADecryptor();

    /**
     * Get the decrypted key
     *
     * @return std::string decrypted key
     */
    inline std::string getDecryptedKey() const { return _decryptedKey; }

    /**
     * Get the pkey from given rsa file
     *
     * @param filepath: path to the rsa file
     * @return EVP_PKEY
     */
    EVP_PKEY* getEvpPkeyFromFile(const std::string &filepath); // TODO Delete cause unnecessary now

    /**
     * Get the binary content from the encrypted key file
     *
     * @param filepath: path to the encrypted key file
     * @return std::string encrypted key content
     */
    std::string getBinKeyFileContents(const std::string &filepath);

    /**
     * Decrypts the given message string
     *
     * @param pkey: EVP_PKEY to decrypt the cipher message string
     * @param msg: message as std::string
     * @return boolean, true if decryption was successful else false
     */
    bool decrypt(EVP_PKEY *pkey, const std::string &msg);
};


} // namespace butterfly

#endif //BUTTERFLY_RSADECRYPTOR_H