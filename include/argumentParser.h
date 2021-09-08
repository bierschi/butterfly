
#ifndef BUTTERFLY_ARGUMENT_PARSER_H
#define BUTTERFLY_ARGUMENT_PARSER_H

#include <iostream>

#include "app.h"
#include "logger.h"

namespace butterfly
{

/**
 * Class ArgumentParser to parse provided arguments
 */
class ArgumentParser
{

private:
    std::string _dir, _encrypt, _decrypt, _protected, _serverpKey, _config, _help, _version, _usage, _options;

    /**
     * Prints the help message
     */
    void printHelp();

    /**
     * Prints the version message
     */
    void printVersion();

public:

    struct Arguments
    {
        std::string _dir, _encrypt, _decrypt, _serverpKey, _config;
        bool _protected;
        const std::string _version;

        Arguments() : _dir(""), _encrypt(""), _decrypt(""), _serverpKey(""), _config(""), _protected(false), _version(PROJECT_VER)
        {}
    };

    /**
     * ArgumentParser default constructor
     */
    ArgumentParser();

    /**
     * ArgumentParser Destructor
     */
    ~ArgumentParser() = default;

    /**
     * Parses the given application arguments
     */
    Arguments parseArgs(const int &argc, char *argv[]);

};

} // namespace butterfly

#endif //BUTTERFLY_ARGUMENT_PARSER_H
