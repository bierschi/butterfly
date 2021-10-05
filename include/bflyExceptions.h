
#ifndef BUTTERFLY_BFLYEXCEPTIONS_H
#define BUTTERFLY_BFLYEXCEPTIONS_H

#include <exception>
#include <iostream>

namespace butterfly
{

/**
 * Class ButterflyException
 */
class ButterflyException : public std::exception
{

public:
    std::string _error;

    explicit ButterflyException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class EncryptionException
 */
class EncryptorException : public ButterflyException
{

public:
    explicit EncryptorException(const std::string &error) : ButterflyException(error) {}

};

/**
 * Class DecryptorException
 */
class DecryptorException : public ButterflyException
{

public:
    explicit DecryptorException(const std::string &error) : ButterflyException(error) {}

};

/**
 * Class RSAEncryptionException
 */
class RSAEncryptionException : public EncryptorException
{

public:
    explicit RSAEncryptionException(const std::string &error) : EncryptorException(error) {}

};

/**
 * Class RSADecryptionException
 */
class RSADecryptionException : public DecryptorException
{

public:
    explicit RSADecryptionException(const std::string &error) : DecryptorException(error) {}

};

/**
 * Class AESEncryptionException
 */
class AESEncryptionException : public EncryptorException
{

public:
    explicit AESEncryptionException(const std::string &error) : EncryptorException(error) {}

};

/**
 * Class AESDecryptionException
 */
class AESDecryptionException : public DecryptorException
{

public:
    explicit AESDecryptionException(const std::string &error) : DecryptorException(error) {}

};

/**
 * Class SQLDatabaseException
 */
class SQLDatabaseException : public ButterflyException
{

public:
    explicit SQLDatabaseException(const std::string &error) : ButterflyException(error) {}
};


} // namespace butterfly

#endif //BUTTERFLY_BFLYEXCEPTIONS_H
