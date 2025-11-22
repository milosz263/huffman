#include "cli.hpp"

int main (int argc, char** argv)
{
    std::string exename = "";
    if (argv[0] != nullptr)
        exename = fs::path(argv[0]).filename();
    
    if (argc < 2)
    {
        printUsage(exename);
        exit(EXIT_FAILURE);
    }
}