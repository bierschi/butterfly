
#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <iostream>
#include <vector>
#include <cstring>

namespace tools
{

/**
 * Class ArgumentParser to parse provided command line arguments
 */
class ArgumentParser
{

private:
    int _argc;
    char **_argv;
    std::string _projectName;
    std::vector<std::string> _args;

    /**
     * Shows the Application Usage
     */
    void showUsage() const;

public:

    struct Arguments
    {
        std::string ip;
        int port;
        bool client, server;
        Arguments() : client(false), server(false)
        {}
    };

    /**
     * Constructor ArgumentParser
     *
     * Usage:
     *      std::shared_ptr<tools::ArgumentParser> _argparse = std::make_shared<tools::ArgumentParser>(argc, argv);
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

} // namespace tools

#endif //ARGUMENT_PARSER_H
