
#ifndef RANSOMWARE_ARGUMENT_PARSER_H
#define RANSOMWARE_ARGUMENT_PARSER_H

#include <iostream>

#include "app.h"
#include "logger.h"

class ArgumentParser {

private:
    std::string _help, _version, _options, _usage;

    /**
     *
     */
    void printHelp();

    /**
     *
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
     *
     */
    void parseArgs(const int &argc, char* argv[]);

};
#endif //RANSOMWARE_ARGUMENT_PARSER_H
