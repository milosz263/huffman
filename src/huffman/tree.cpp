#include "huffman/tree.hpp"
namespace huffman::internal {

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

}