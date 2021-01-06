
#ifndef BUTTERFLY_RSAENCRYPTOR_H
#define BUTTERFLY_RSAENCRYPTOR_H

#include <fstream>

#include "rsa.h"

namespace butterfly {

/**
 * Class RSAEncryptor to provide methods for simple rsa encryption
 */
class RSAEncryptor : public CryptoRSA {

private:
    const std::string _cPrivateRsaKeyFilename, _cPublicKeyFilename, _encAESKeyFilename;

    unsigned char *_ciphertextKey;

    /**
     * Validates the length of given string with the max rsa block size
     */
    bool validateStringLengthForRSA(const std::string &msg);

    /**
     * Saves the encrypted key file
     *
     * @param ciphertextKey: key as ciphertext
     * @param ciphertextLength: length of the ciphertext
     */
    void saveEncryptedKeyFile(unsigned char *ciphertextKey, int ciphertextLength);

public:
    /**
     * Constructor RSAEncryptor
     *
     * @param keySize: size of the key
     */
    explicit RSAEncryptor(const std::string &AESKeyFile, int keySize=2048);

    /**
     * Destructor RSAEncryptor
     */
    ~RSAEncryptor();

    /**
     * Saves the private rsa key file for the client machine
     */
    void saveClientPrivateRSAKeyFile();

    /**
     * Saves the public key file for the client machine
     */
    void saveClientPublicKeyFile();
    
    /**
     * Encrypts the given message string
     *
     * @param msg: message as std::string
     * @return boolean, true if encryption was successful else false
     */
    bool encrypt(const std::string &msg);

};

} //namespace butterfly

#endif //BUTTERFLY_RSAENCRYPTOR_H
