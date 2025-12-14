#include "huffman/tree.hpp"

bytecount CountBytes(ILoader &loader)
{
    bytecount ret{};
    loader.seek(0);
    while(!loader.end())
    {
        ret[loader.get()]++;
    }
    return ret;
}