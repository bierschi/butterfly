
#ifndef BUTTERFLY_RSAENCRYPTOR_H
#define BUTTERFLY_RSAENCRYPTOR_H

#include "rsa.h"
#include "utils.h"
#include "params.h"
#include "exceptions.h"

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
    bool validateStringLengthForRSA(const std::string &msg, const int &keysize) override;

    /**
     * Writes the RSA file that includes the RSA EK and RSA IV to the filesystem
     *
     * @param type: enum RSAKEY_TYPE
     * @return True if writing was successful
     */
    bool writeRSAFileToSystem(const RSAKEY_TYPE &type);

public:

    /**
     * Constructor RSAEncryptor
     *
     * @param keySize: size of the key
     */
    explicit RSAEncryptor(int keySize);

    /**
     * Constructor RSAEncryptor to init rsa key from key string or file
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
    static void writeEncMSGToFile(const std::string &filename, const std::string ciphertextMsg, int ciphertextMsgLength);

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
     * @param type: enum RSAKEY_TYPE
     * @return size of the encrypted message
     */
    int encryptEVP(EVP_PKEY *pkey, const std::string &decMSG, const RSAKEY_TYPE &type);
};

} //namespace rsa

} //namespace butterfly

#endif //BUTTERFLY_RSAENCRYPTOR_H
