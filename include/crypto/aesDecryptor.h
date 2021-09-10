
#ifndef BUTTERFLY_AESDECRYPTOR_H
#define BUTTERFLY_AESDECRYPTOR_H

#include "aes.h"
#include "utils.h"
#include "params.h"
#include "exceptions.h"

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
     */
    AESDecryptor();

    /**
     * Destructor AESDecryptor
     */
    ~AESDecryptor() = default;

    /**
     * Decrypts the given filename
     *
     * @param filename: name of the file
     */
    void decryptFile(const std::string &filename);

};

} // namespace aes

} // namespace butterfly

#endif //BUTTERFLY_AESDECRYPTOR_H
