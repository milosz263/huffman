#include "cli.hpp"

void getFilename(int argc, char **argv, int i, std::string &filename)
{
    if (filename != "")
    {
        exitDuplicateParameter(argv[i]);
    }
    if (i+1 >= argc)
    {
        exitNoFileSpecified(argv[i]);
    }
    filename = argv[i+1];
}

void exitUsage(std::string exename)
{
    if (exename == "")
        exename = "huffman";
    std::cerr 
        << "Usage: "<< exename << " [option] -i <inputFile> -o <outputfile>\n"
        << "  -c\tEncode inputFile to outputFile.\n"
        << "  -d\tDecode inputFile to outputFile.\n";
    exit(EXIT_FAILURE);
}

void exitBadParameter(std::string param)
{
    std::cerr
        << "error: Bad parameter: " << param << '\n';
    exit(EXIT_FAILURE);
}

void exitDuplicateParameter(std::string param)
{
    std::cerr
        << "error: Duplicate parameter: " << param << '\n';
    exit(EXIT_FAILURE);
}

void exitNoFileSpecified(std::string param)
{
    std::cerr
        << "error: " << param << ": No file specified.\n";
    exit(EXIT_FAILURE);
}

void exitInputFileDoesntExist(std::string filename)
{
    std::cerr
        << "error: Input file \"" << filename << "\" doesn't exist.";
    exit(EXIT_FAILURE);
}

void exitOutputFileExists(std::string filename)
{
    std::cerr
        << "error: Output file \"" << filename << "\" already exists.";
    exit(EXIT_FAILURE);
}

void exitFlagsConflict()
{
    std::cerr
        << "error: encode flag and decode flag can't be used alongside.";
    exit(EXIT_FAILURE);
}
