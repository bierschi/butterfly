
#ifndef BUTTERFLY_CRYPTOSECURITY_H
#define BUTTERFLY_CRYPTOSECURITY_H

#include <string>
#include <iostream>

#include "bflyParams.h"
#include "bflyUtils.h"
#include "logger.h"

namespace butterfly
{

namespace hybrid
{

/**
 * Class CryptoSecurity for security related tasks
 */
class CryptoSecurity
{


public:
    /**
     * Default Constructor CryptoSecurity
     */
    CryptoSecurity() = default;

    /**
     * Default Destructor CryptoSecurity
     */
    ~CryptoSecurity() = default;

    /**
    * Saves the unencrypted AESKeyPair to the filesystem
    *
    * @param aesKeyPair: aesKeyPair string
    */
    static void saveUnencryptedAESKeyPair(const std::string &aesKeyPair);

    /**
    * Checks if bfly encryption files already exists (CPrivateRSA.bin, AES.bin, RSA.bin)
    */
    static bool areEncryptionFilesAvailable();

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
};

} // namespace hybrid

} // namespace butterfly
#endif // BUTTERFLY_CRYPTOSECURITY_H
