
#ifndef BUTTERFLY_RSADECRYPTOR_H
#define BUTTERFLY_RSADECRYPTOR_H

#include "rsa.h"

namespace butterfly {

class RSADecryptor : public CryptoRSA {

private:
    std::string _decryptedKey;

public:

    RSADecryptor();

    ~RSADecryptor();

    /**
     * Decrypts the given message string
     *
     * @param msg: message as std::string
     * @return boolean, true if decryption was successful else false
     */
    bool decrypt(const std::string &msg);
};


} // namespace butterfly

#endif //BUTTERFLY_RSADECRYPTOR_H
