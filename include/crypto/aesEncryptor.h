
#ifndef BUTTERFLY_AESENCRYPTOR_H
#define BUTTERFLY_AESENCRYPTOR_H

#include "aes.h"
#include "bflyUtils.h"
#include "bflyParams.h"
#include "bflyExceptions.h"

namespace butterfly
{

namespace aes
{

/**
 * Class AESEncryptor to encrypt files with AES
 */
class AESEncryptor : public CryptoAES
{

private:

public:

    /**
     * Constructor AESEncryptor
     */
    AESEncryptor();

    /**
     * Destructor AESEncryptor
     */
    ~AESEncryptor() = default;

    /**
     * Encrypts the given filename
     *
     * @param filename: name of the file
     */
    void encryptFile(const std::string &filename);

};

} // namespace aes

} // namespace butterfly

#endif //BUTTERFLY_AESENCRYPTOR_H
