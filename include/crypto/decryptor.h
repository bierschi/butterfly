
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include "crypto/rsaDecryptor.h"
#include "params.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Decryptor to decrypt the AES and the CPrivateRSA key
 */
class Decryptor
{

private:
    std::string _decryptedCPrivateRSA, _decryptedAESKey;
    std::unique_ptr<rsa::RSADecryptor> _rsaDecryptorAESKey, _rsaDecryptorCPrivateRSA;

public:
    /**
     * Constructor Decryptor
     */
    Decryptor();

    /**
     * Destructor Decryptor
     */
    ~Decryptor();

    std::string decryptCPrivateRSA(const std::string &keyFromServer);

    std::string decryptAESKey(const std::string &decryptedCPrivateRSA);
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
