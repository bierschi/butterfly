
#ifndef BUTTERFLY_RSAENCRYPTOR_H
#define BUTTERFLY_RSAENCRYPTOR_H

#include "rsa.h"

namespace butterfly {

/**
 * Class RSAEncryptor to provide methods for simple rsa encryption
 */
class RSAEncryptor : public CryptoRSA {

private:
    std::string _encryptedKey;
    const std::string _cPrivateRSAKeyFilename, _cPublicKeyFilename;

    /**
     * Validates the length of given string with the max rsa block size
     */
    bool validateStringLengthForRSA(const std::string &msg);

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
    ~RSAEncryptor();

    /**
     * Get the encrypted key
     *
     * @return: encrypted key as std::string
     */
    inline std::string getEncryptedKey() const { return _encryptedKey; }

    /**
     * Saves the encrypted key file
     *
     * @param ciphertextKey: key as ciphertext
     * @param ciphertextLength: length of the ciphertext
     */
    void saveEncryptedKeyFile(const std::string &filename, const std::string &ciphertextKey, int keyLength);

    /**
     * Encrypts the given message string
     *
     * @param msg: message as std::string
     * @return boolean, true if encryption was successful else false
     */
    bool encrypt(EVP_PKEY *pkey, const std::string &msg);

    /**
     * Saves the private rsa key file for the client machine
     */
    void saveClientPrivateRSAKeyFile();

    /**
     * Saves the public key file for the client machine
     */
    void saveClientPublicKeyFile();

};

} //namespace butterfly

#endif //BUTTERFLY_RSAENCRYPTOR_H
