
#ifndef BUTTERFLY_AESENCRYPTOR_H
#define BUTTERFLY_AESENCRYPTOR_H

#include "aes.h"
#include "utils.h"
#include "params.h"
#include "exceptions.h"

namespace butterfly
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
     * Get the AESKey
     *
     * @return AESKey as std::string
     */
    std::string getAESKey() const;

    /**
     * Get the AESIv
     *
     * @return AESIv as std::string
     */
    std::string getAESIv() const;

    /**
     * Encrypts the given filename
     *
     * @param filename: name of the file
     */
    void encryptFile(const std::string &filename);

};

} // namespace butterfly

#endif //BUTTERFLY_AESENCRYPTOR_H
