
#ifndef BUTTERFLY_ARGUMENT_PARSER_H
#define BUTTERFLY_ARGUMENT_PARSER_H

#include <iostream>

#include "app.h"
#include "logger.h"

namespace butterfly
{

class ArgumentParser
{

private:
    std::string _help, _version, _options, _usage;

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
        std::string _config;
        std::string _dir;
        const std::string _version;

        Arguments() : _config(""), _dir(""), _version(PROJECT_VER)
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
