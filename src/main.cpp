#include "cli.hpp"
#include "writer.hpp"
#include "loader.hpp"
#include "huffman.hpp"
#include "data.hpp"

int main(int argc, char** argv)
{
    //argv parsing
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
                decode = true;
                break;
            case 'i':
                getFilename(argc,argv,i,inpath);
                i++;
                if (!fs::exists(fs::path(inpath)))
                    exitInputFileDoesntExist(inpath);
                break;
            case 'o':
                getFilename(argc,argv,i,outpath);
                i++;
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
    if (inpath == "")
    {
        exitNoInputFileSpecified();
    }
    if (outpath == "")
    {
        exitNoOutputFileSpecified();
    }

    //doing

    auto loader = getLoaderFromFile(fs::path(inpath));
    auto writer = ToFileWriter(fs::path(outpath));

    if(decode)
        huffman::Decode(*loader, writer);
    else
        huffman::Encode(*loader, writer);

    return EXIT_SUCCESS;
}