
#include <memory>

#include "butterfly.h"
#include "bflyExceptions.h"

int main(int argc, char *argv[])
{
    try
    {

        std::unique_ptr<butterfly::Butterfly> blfy(new butterfly::Butterfly(argc, argv));
        blfy->run();

    } catch ( butterfly::ButterflyException &e )
    {
        std::cout << "Unhandled BFLY " << e.getType() << ": " << e.what() << std::endl;
    }

    return 0;
}
