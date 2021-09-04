
#ifndef BUTTERFLY_RSAENCRYPTOR_H
#define BUTTERFLY_RSAENCRYPTOR_H

#include "rsa.h"
#include "utils.h"
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
    std::string _encryptedKey;

    /**
     * Validates the length of given string with the max rsa block size
     */
    bool validateStringLengthForRSA(const std::string &msg, const int &keysize) override;

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
    virtual ~RSAEncryptor() = default;

    /**
     * Get the encrypted key
     *
     * @return: encrypted key as std::string
     */
    inline std::string getEncryptedKey() const
    { return _encryptedKey; }

    /**
     * Saves the encrypted key file
     *
     * @param ciphertextKey: key as ciphertext
     * @param ciphertextLength: length of the ciphertext
     */
    static void saveEncryptedKeyFile(const std::string &filename, const std::string ciphertextKey, int keyLength);

    /**
     * Encrypts the given message string
     *
     * @param msg: message as std::string
     */
    void encrypt(EVP_PKEY *pkey, const std::string &msg);

};

} //namespace rsa

} //namespace butterfly

#endif //BUTTERFLY_RSAENCRYPTOR_H
