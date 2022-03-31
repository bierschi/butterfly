#include <iostream>
#include <memory>

#include "argumentParser.h"

int main(int argc, char* argv[])
{

    std::unique_ptr<tools::ArgumentParser> argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = argparse->parseArgs();

    return 0;
}

