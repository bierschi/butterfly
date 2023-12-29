
#ifndef BUTTERFLY_AESDECRYPTOR_H
#define BUTTERFLY_AESDECRYPTOR_H

#include "aes.h"
#include "bflyUtils.h"
#include "bflyParams.h"
#include "bflyExceptions.h"

namespace butterfly
{

namespace aes
{

/**
 * Class AESDecryptor to decrypt files with AES
 */
class AESDecryptor : public CryptoAES
{

private:

public:

    /**
     * Constructor AESDecryptor
     *
     *  Usage:
     *       std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor(new butterfly::aes::AESDecryptor());
     *       aesDecryptor->decryptFile("/home/user/test.bfly");
     */
    AESDecryptor();

    /**
     * Destructor AESDecryptor
     */
    ~AESDecryptor() override = default;

    /**
     * Decrypts the given filename
     *
     * @param bflyFileName: name of the file with bfly extension
     */
    void decryptFile(const std::string &bflyFileName);
    void decryptFile2(const std::string &bflyFileName);
};

} // namespace aes

} // namespace butterfly

#endif //BUTTERFLY_AESDECRYPTOR_H
