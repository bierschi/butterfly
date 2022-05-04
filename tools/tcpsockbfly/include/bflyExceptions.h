
#ifndef TCPSOCKBFLY_BFLYEXCEPTIONS_H
#define TCPSOCKBFLY_BFLYEXCEPTIONS_H

#include <exception>
#include <iostream>

namespace tools
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

    virtual std::string getType() const
    {
        return "ButterflyException";
    }
};

/**
 * Class EncryptionException
 */
class EncryptorException : public ButterflyException
{

public:
    explicit EncryptorException(const std::string &error) : ButterflyException(error) {}

    std::string getType() const override
    {
        return "EncryptorException";
    }
};

/**
 * Class DecryptorException
 */
class DecryptorException : public ButterflyException
{

public:
    explicit DecryptorException(const std::string &error) : ButterflyException(error) {}

    std::string getType() const override
    {
        return "DecryptorException";
    }
};

/**
 * Class RSAEncryptionException
 */
class RSAEncryptionException : public EncryptorException
{

public:
    explicit RSAEncryptionException(const std::string &error) : EncryptorException(error) {}

    std::string getType() const override
    {
        return "RSAEncryptionException";
    }
};

/**
 * Class RSADecryptionException
 */
class RSADecryptionException : public DecryptorException
{

public:
    explicit RSADecryptionException(const std::string &error) : DecryptorException(error) {}

    std::string getType() const override
    {
        return "RSADecryptionException";
    }
};

/**
 * Class AESEncryptionException
 */
class AESEncryptionException : public EncryptorException
{

public:
    explicit AESEncryptionException(const std::string &error) : EncryptorException(error) {}

    std::string getType() const override
    {
        return "AESEncryptionException";
    }
};

/**
 * Class AESDecryptionException
 */
class AESDecryptionException : public DecryptorException
{

public:
    explicit AESDecryptionException(const std::string &error) : DecryptorException(error) {}

    std::string getType() const override
    {
        return "AESDecryptionException";
    }
};

/**
 * Class SQLDatabaseException
 */
class SQLDatabaseException : public ButterflyException
{

public:
    explicit SQLDatabaseException(const std::string &error) : ButterflyException(error) {}

    std::string getType() const override
    {
        return "SQLDatabaseException";
    }
};

/**
 * Class SocketException
 */
class SocketException : public ButterflyException
{

public:
    explicit SocketException(const std::string &error) : ButterflyException(error) {}

    std::string getType() const override
    {
        return "SocketException";
    }
};

/**
 * Class FileNotFoundException
 */
class FileNotFoundException : public ButterflyException
{

public:
    explicit FileNotFoundException(const std::string &error) : ButterflyException(error) {}

    std::string getType() const override
    {
        return "FileNotFoundException";
    }
};

/**
 * Class ConnectionException
 */
class ConnectionException : public ButterflyException
{

public:
    explicit ConnectionException(const std::string &error) : ButterflyException(error) {}

    std::string getType() const override
    {
        return "ConnectionException";
    }
};

} // namespace tools

#endif //TCPSOCKBFLY_BFLYEXCEPTIONS_H
