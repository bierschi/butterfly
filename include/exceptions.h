
#ifndef BUTTERFLY_EXCEPTIONS_H
#define BUTTERFLY_EXCEPTIONS_H

#include <exception>
#include <iostream>

namespace butterfly
{

/**
 * Class RSAEncryptionException
 */
class RSAEncryptionException : public std::exception
{

private:
    std::string _error;

public:
    explicit RSAEncryptionException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class RSADecryptionException
 */
class RSADecryptionException : public std::exception
{

private:
    std::string _error;

public:
    explicit RSADecryptionException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class AESEncryptionException
 */
class AESEncryptionException : public std::exception
{

private:
    std::string _error;

public:
    explicit AESEncryptionException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class AESDecryptionException
 */
class AESDecryptionException : public std::exception
{

private:
    std::string _error;

public:
    explicit AESDecryptionException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class EncryptionException
 */
class EncryptorException : public std::exception
{

private:
    std::string _error;

public:
    explicit EncryptorException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class DecryptorException
 */
class DecryptorException : public std::exception
{

private:
    std::string _error;

public:
    explicit DecryptorException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

/**
 * Class SQLDatabaseException
 */
class SQLDatabaseException : public std::exception
{

private:
    std::string _error;

public:
    explicit SQLDatabaseException(const std::string &error) : _error(error) {}

    const char * what() const noexcept override
    {
        return _error.c_str();
    }
};

} // namespace butterfly

#endif //BUTTERFLY_EXCEPTIONS_H
