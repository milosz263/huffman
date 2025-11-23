#include "cli.hpp"

#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Command-line arguments are handled directly here.
 */

int main(int argc, char** argv)
{
    std::string exename = "";
    if (argv[0] != nullptr)
        exename = fs::path(argv[0]).filename();
    
    if (argc < 2)
    {
        exitUsage(exename);
    }

    bool decode = false;
    bool encode = false;
    std::string inpath = "";
    std::string outpath = "";

    std::string argument;
    for (int i = 1; i < argc; i++)
    {
        argument = argv[i];
        if (argument[0] != '-' || argument.size() != 2)
        {
            exitBadParameter(argument);
        }
        switch (argument[1])
        {
            case 'c':
                encode = true;
                break;
            case 'd':
                decode = false;
                break;
            case 'i':
                getFilename(argc,argv,i,inpath);
                if (!fs::exists(fs::path(inpath)))
                    exitInputFileDoesntExists(inpath);
                break;
            case 'o':
                getFilename(argc,argv,i,outpath);
                if (fs::exists(fs::path(outpath)))
                    exitOutputFileExists(outpath);
                break;
            default:
                exitBadParameter(argument);
                break;
        }
    }
    if (decode && encode)
    {
        exitFlagsConflict();
    }
    return EXIT_SUCCESS;
}