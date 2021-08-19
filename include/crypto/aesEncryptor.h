
#ifndef BUTTERFLY_AESENCRYPTOR_H
#define BUTTERFLY_AESENCRYPTOR_H

#include "aes.h"
#include "utils.h"
#include "params.h"
#include "exceptions.h"

namespace butterfly
{

class AESEncryptor : public CryptoAES
{
private:

public:
    AESEncryptor();
    ~AESEncryptor() = default;

    std::string getAESKey() const;
    std::string getAESIv() const;

    void encryptFile(const std::string &filename);

    void encryptFile_old(char *filename);

};

} // namespace butterfly

#endif //BUTTERFLY_AESENCRYPTOR_H
