
#ifndef BUTTERFLY_RSAENCRYPTOR_H
#define BUTTERFLY_RSAENCRYPTOR_H

#include <fstream>

#include "rsa.h"

namespace butterfly {

/**
 *
 */
class RSAEncryptor : public CryptoRSA {

private:
    const std::string _cPrivateRsaKeyFilename, _encryptedKeyFilename;

    unsigned char *_ciphertextKey;

public:
    /**
     *
     */
    RSAEncryptor();

    /**
     *
     */
    ~RSAEncryptor();

    void saveClientPrivateRSAKeyFile();
    void saveEncryptedKeyFile(unsigned char *ciphertextKey, int ciphertextLength);
    void encrypt(const std::string &key);

};

} //namespace butterfly

#endif //BUTTERFLY_RSAENCRYPTOR_H