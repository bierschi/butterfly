
#include <memory>

#include "argument_parser.h"

int main(int argc, char* argv[]) {

    // parse args with the argument parser
    std::unique_ptr<butterfly::ArgumentParser> argparse(new butterfly::ArgumentParser());
    argparse->parseArgs(argc, argv);

    return 0;
}