
#ifndef BUTTERFLY_RSADECRYPTOR_H
#define BUTTERFLY_RSADECRYPTOR_H

#include "rsa.h"
#include "utils.h"
#include "params.h"
#include "exceptions.h"

namespace butterfly
{

namespace rsa
{

/**
 * Class RSADecryptor to provide methods for simple rsa decryption
 */
class RSADecryptor : public CryptoRSA
{

private:
    std::string _decryptedMessage;

    /**
     * Validates the length of given string with the RSA key size
     */
    bool validateStringLengthForRSA(const std::string &msg, const int &keysize) override;

    /**
     * Reads the RSA EK und RSA IV from the System
     *
     * @param type: type of the saved file
     * @param encKey: rsa encrypted key
     * @param iv: rsa iv
     */
    void readRSAFilesFromSystem(const std::string &type, std::string &encKey, std::string &iv);

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
    explicit RSADecryptor(const std::string &key);

    /**
     * Destructor RSADecryptor
     */
    ~RSADecryptor() override = default;

    /**
     * Get the decrypted Message
     *
     * @return std::string decrypted Message
     */
    inline std::string getDecryptedMessage() const
    { return _decryptedMessage; }

    /**
     * Get the binary content from the encrypted key file
     *
     * @param filepath: path to the encrypted key file
     * @return std::string encrypted key content
     */
    static std::string getBinKeyFileContents(const std::string &filepath);

    /**
     * Decrypts the given message string
     *
     * @param pkey: EVP_PKEY to decrypt the cipher message string
     * @param msg: message as std::string
     */
    void decrypt(EVP_PKEY *pkey, const std::string &msg);

    /**
     * Decrypts the given message string with EVP methods
     *
     * @param pkey: EVP_PKEY to decrypt the cipher message string
     * @param msg: message as std::string
     */
    void decryptEVP(EVP_PKEY *pkey, const std::string &msg, const std::string &type);
};

} // namespace rsa

} // namespace butterfly

#endif //BUTTERFLY_RSADECRYPTOR_H
