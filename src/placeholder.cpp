#warning Some functions have not been implemented yet and uses placeholder definitions.

#include "huffman.hpp"
#include <iostream>

// static void rewrite(ILoader &loader, IWriter &writer)
// {
//     while (!loader.end())
//     {
//         writer.write(loader.get());
//     }
//     writer.close();
// }

static void rewrite_chunk(ILoader &loader, IWriter &writer)
{
    auto size = loader.size();
    auto ch = loader.getChunk(size);
    writer.writeChunk(ch);
    writer.close();
}

// void huffman::Encode(ILoader &loader, IWriter &writer)
// {
//     std::cout << "Calling huffman::Encode(), rewriting by byte" << std::endl;
//     rewrite(loader, writer);
// }

void huffman::Decode(ILoader &loader, IWriter &writer)
{
    std::cout << "Calling huffman::Decode() rewriting by chunk" << std::endl;
    rewrite_chunk(loader, writer);
}