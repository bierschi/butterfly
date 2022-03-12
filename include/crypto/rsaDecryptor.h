
#ifndef BUTTERFLY_RSADECRYPTOR_H
#define BUTTERFLY_RSADECRYPTOR_H

#include "rsa.h"
#include "bflyUtils.h"
#include "bflyParams.h"
#include "bflyExceptions.h"

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
    unsigned long _cPrivateRSAKeyLength, _aesKeyLength, _aesIvLength;

    /**
     * Validates the length of given string with the RSA key size
     */
    bool validateStringLengthForRSA(const std::string &msg, const int &keysize);

    /**
     * Reads the RSA file that includes the RSA EK and RSA IV from the host machine
     *
     * @param rsakeysType: type of the saved file
     * @param encKey: rsa encrypted key
     * @param iv: rsa iv
     */
    void readRSAFileFromSystem(const RSAKEY_TYPE &rsakeysType, std::string &encKey, std::string &iv);

public:

    /**
     * Constructor RSADecryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::rsa::RSADecryptor> rsaDecryptor(new butterfly::rsa::RSADecryptor(""));
     *       rsaDecryptor->getDecryptedMessage();
     */
    RSADecryptor() = delete;

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
    static std::string readEncMSGFromFile(const std::string &filepath);

    /**
     * Decrypts the given message string
     *
     * @param pkey: EVP_PKEY to decrypt the cipher message string
     * @param encMSG: encrypted message as std::string
     * @param decMSG: decrypted message as std::string
     * @return size of the decrypted message
     */
    int decrypt(EVP_PKEY *pkey, const std::string &encMSG, std::string &decMSG);

    /**
     * Decrypts the given message string with EVP methods
     *
     * @param pkey: EVP_PKEY to decrypt the cipher message string
     * @param encMSG: encrypted Message as std::string
     * @param decMSG: decrypted Message as std:.string
     * @param type: enum RSAKEY_TYPE
     * @return size of the decrypted message
     */
    int decryptEVP(EVP_PKEY *pkey, const std::string &encMSG, std::string &decMSG, const RSAKEY_TYPE &type);
};

} // namespace rsa

} // namespace butterfly

#endif //BUTTERFLY_RSADECRYPTOR_H
