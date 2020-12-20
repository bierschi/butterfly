
#include "argument_parser.h"

ArgumentParser::ArgumentParser() {

    _usage = "Usage: \n \t\t ransomware --path --logging\n\n";
    _options = "Options\n";
    _help = "-h, --help\t\tPrint help message\n";
    _version = "-v, --version\tPrint current version";

    // Logger is disabled as default setting
    Logger::disable();
}

ArgumentParser::~ArgumentParser() {

}

void ArgumentParser::parseArgs(const int &argc, char* argv[]) {

    if (argc > 1) {

        for (int i = 1; i < argc; i++) {

            std::string arg = argv[i];

            if (arg == "-h" || arg == "--help") {
                printHelp();
            } else if (arg == "-v" || arg == "--version") {
                printVersion();
            } else if (arg == "-c" || arg == "--config") {

                // check end of argc
                if ( i + 1 < argc && (!strchr(argv[i+1], '--')) ) {
                    std::string configPath = argv[i+1];

                    // init logger instance
                    Logger::initFromConfig(configPath);

                } else {
                    std::cout << "--config option requires one argument!" << std::endl;
                }
            }
        }
    } else {
        printHelp();
    }

}

void ArgumentParser::printHelp() {

    std::string output;
    output += _usage + _options + _help + _version;
    std::cout << output << std::endl;
}

void ArgumentParser::printVersion() {
    std::cout << "Version: " << PROJECT_VER << std::endl;
}