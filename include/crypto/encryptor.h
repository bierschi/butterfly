
#ifndef BUTTERFLY_ENCRYPTOR_H
#define BUTTERFLY_ENCRYPTOR_H

#include "crypto/rsaEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "params.h"

namespace butterfly {

/**
 * Class Encryptor to encrypt the AES and the CPrivateRSA key
 */
class Encryptor {

private:
    int _keySize;
    std::string _aesKey = "0123456789abcdefghijklabcdefg";
    std::unique_ptr<RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorCPrivateRSA;

public:
    /**
     * Constructor Encryptor
     */
    explicit Encryptor(int keySize=2048);

    /**
     * Destructor Encryptor
     */
    ~Encryptor();

    void encryptAESKey();

    void encryptCPrivateRSA();
};

} // namespace butterfly

#endif //BUTTERFLY_ENCRYPTOR_H
