#include "huffman/tree.hpp"
#include <cmath>

namespace huffman::internal {

void writetable(IWriter &writer, codetable codes)
{
    byte codesize[2];
    chunk bincode;
    //1. Section header: 00 01, or 256 in little endian
    writer.write(0);
    writer.write(1);
    //2. code for end of file, without character
    splituint16(codes[eof].bitsize, codesize);
    writer.write(codesize[0]);
    writer.write(codesize[1]);
    //3. Rest of codes, in format: [0] - character, [1-2] - code size (in bits, uint16-le), [3+] code, ...
    for (byte i = 0; /* check at the end of loop */; i++)
    {
        if (codes[i].bitsize != 0)
        {
            writer.write(i);
            splituint16(codes[i].bitsize, codesize);
            writer.write(codesize[0]);
            writer.write(codesize[1]);
            bincode = savebinarycode(codes[i]);
            writer.writeChunk(bincode);
        }
        if (i == 255)
            break;
    }
}
chunk savebinarycode(code code)
{
    chunk ret(std::ceil(code.bitsize / 8.0));
    for (uint_fast16_t i = 0; i < ret.size(); i++)
    {
        byte curr = 0;
        for (uint_fast16_t j = 0; j < 8; j++)
        {
            auto pos = i*8 + j;
            if (pos > code.bitsize)
                break;
            curr <<= 1;
            if (code.data[pos])
                curr |= 1;
        }
        ret[i] = curr;
    }
    return ret;
}
}