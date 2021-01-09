
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include "crypto/rsaDecryptor.h"

namespace butterfly {

/**
 * Class Decryptor to decrypt the AES and the CPrivateRSA key
 */
class Decryptor {

private:
    std::unique_ptr<RSADecryptor> _rsaDecryptorAESKey, _rsaDecryptorCPrivateRSA;
    std::string _decryptedCPrivateRSA, _decryptedAESKey;
public:
    /**
     * Constructor Decryptor
     */
    Decryptor();

    /**
     * Destructor Decryptor
     */
    ~Decryptor();

    void decryptCPrivateRSA();
    void decryptAESKey();
};

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
