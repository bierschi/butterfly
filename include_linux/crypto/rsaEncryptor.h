
#ifndef BUTTERFLY_RSAENCRYPTOR_H
#define BUTTERFLY_RSAENCRYPTOR_H

#include "rsa.h"
#include "bflyUtils.h"
#include "bflyParams.h"
#include "bflyExceptions.h"

namespace butterfly
{

namespace rsa
{

/**
 * Class RSAEncryptor to provide methods for simple rsa encryption
 */
class RSAEncryptor : public CryptoRSA
{

private:
    std::string _encryptedMessage;

    /**
     * Validates the length of given string with the max rsa block size
     */
    bool validateStringLengthForRSA(const std::string &msg, const int &keysize);

    /**
     * Writes the RSA file that includes the RSA EK and RSA IV to the filesystem
     *
     * @return True if writing was successful
     */
    bool writeRSAFileToSystem();

public:

    /**
     * Constructor RSAEncryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptor(new butterfly::rsa::RSAEncryptor(2048));
     *       rsaEncryptor->getEncryptedMessage();
     *
     * @param keySize: size of the key
     */
    explicit RSAEncryptor(int keySize);

    /**
     * Constructor RSAEncryptor to init rsa key from key string or file
     *
     *  Usage:
     *       std::unique_ptr<butterfly::rsa::RSAEncryptor> rsaEncryptor(new butterfly::rsa::RSAEncryptor(""));
     *       rsaEncryptor->getEncryptedMessage();
     *
     * @param key: key string or filepath to key
     */
    explicit RSAEncryptor(const std::string &key);

    /**
     * Destructor RSAEncryptor
     */
    ~RSAEncryptor() override = default;

    /**
     * Get the encrypted message
     *
     * @return: encrypted message as std::string
     */
    inline std::string getEncryptedMessage() const
    { return _encryptedMessage; }

    /**
     * Saves the encrypted message to file
     *
     * @param filename: name of the file
     * @param ciphertextMsg: message as ciphertext
     * @param ciphertextMsgLength: length of the ciphertext
     */
    static void writeEncMSGToFile(const std::string &filename, const std::string &ciphertextMsg, int ciphertextMsgLength);

    /**
     * Encrypts the given message string
     *
     * @param pkey: EVP_PKEY for the encryption
     * @param decMSG: message to encrypt
     * @return size of the encrypted message
     */
    int encrypt(EVP_PKEY *pkey, const std::string &decMSG);

    /**
     * Encrypts the given message string with EVP methods
     *
     * @param pkey: EVP_PKEY for the encryption
     * @param decMSG: message to encrypt
     * @return size of the encrypted message
     */
    int encryptEVP(EVP_PKEY *pkey, const std::string &decMSG);
};

} //namespace rsa

} //namespace butterfly

#endif //BUTTERFLY_RSAENCRYPTOR_H
