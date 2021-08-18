
#ifndef BUTTERFLY_AESENCRYPTOR_H
#define BUTTERFLY_AESENCRYPTOR_H

#include "aes.h"
#include "utils.h"
namespace butterfly
{

class AESEncryptor : public CryptoAES
{
private:

public:
    AESEncryptor();
    ~AESEncryptor() = default;

    void encryptFile(char *filename);

};

} // namespace butterfly

#endif //BUTTERFLY_AESENCRYPTOR_H
