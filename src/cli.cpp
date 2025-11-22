#include "cli.hpp"

void printUsage(std::string exename)
{
    if (exename == "")
        exename = "huffman";
    std::cerr 
        << "Usage: "<< exename << " [option] -i <inputFile> -o <outputfile>\n"
        << "  -c\tEncode inputFile to outputFile.\n"
        << "  -d\tDecode inputFile to outputFile.\n";
}