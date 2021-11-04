
#ifndef BUTTERFLY_ARGUMENT_PARSER_H
#define BUTTERFLY_ARGUMENT_PARSER_H

#include <iostream>
#include <vector>

#include "app.h"
#include "logger.h"

namespace butterfly
{

/**
 * Class ArgumentParser to parse provided command line arguments
 */
class ArgumentParser
{

private:
    int _argc;
    char **_argv;
    std::vector<std::string> _args;

    /**
     * Shows the Application Usage
     */
    void showUsage() const;
    /**
     * Shows the version message
     */
    void showVersion() const;

public:

    struct Arguments
    {
        std::string _dir, _encrypt, _decrypt, _serverpKey, _config;
        bool _protected;
        std::string _version;

        Arguments() : _protected(false), _version(PROJECT_VER) {}
    };

    /**
     * Constructor ArgumentParser
     *
     * Usage:
     *      std::shared_ptr<butterfly::ArgumentParser> _argparse = std::make_shared<butterfly::ArgumentParser>(argc, argv);
     *      Arguments args = _argparse->parseArgs();
     *
     * @param argc: number of arguments
     * @param argv: char* of arguments
     */
    ArgumentParser(int argc, char *argv[]);

    /**
     * Destructor ArgumentParser
     */
    ~ArgumentParser() = default;

    /**
     * Parses the command line arguments
     */
    Arguments parseArgs();

};

} // namespace butterfly

#endif //BUTTERFLY_ARGUMENT_PARSER_H
