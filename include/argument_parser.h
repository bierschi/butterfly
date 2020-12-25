
#ifndef RANSOMWARE_ARGUMENT_PARSER_H
#define RANSOMWARE_ARGUMENT_PARSER_H

#include <iostream>

#include "app.h"
#include "logger.h"

namespace butterfly {

class ArgumentParser {

private:
    std::string _help, _version, _options, _usage;
    struct Args {
        std::string config;
        std::string dir;
        std::string version;
    };

    /**
     * Prints the help message
     */
    void printHelp();

    /**
     * Prints the version message
     */
    void printVersion();

public:
    /**
     * ArgumentParser default constructor
     */
    ArgumentParser();

    /**
     * ArgumentParser Destructor
     */
    ~ArgumentParser();

    /**
     * Parses the given application arguments
     */
    void parseArgs(const int &argc, char *argv[]);

};

} // namespace butterfly

#endif //RANSOMWARE_ARGUMENT_PARSER_H
