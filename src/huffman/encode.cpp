#include "huffman/tree.hpp"
#include "huffman.hpp"
#include "huffman/internal.hpp"
#include <cmath>

static inline void writecodedbyte(huffman::internal::code &x, uint_fast8_t &bytepos, IWriter &writer, byte &currentwrite)
{
    for (size_t i = 0; i < x.bitsize; i++)
    {
        if (bytepos == 8)
        {
            bytepos = 0;
            writer.write(currentwrite);
            currentwrite = 0;
        }
        byte bit = 0;
        if (x.data[i])
        {
            bit = 1 << bytepos;
            currentwrite |= bit;
        }
        bytepos++;
    }
}

void huffman::Encode(ILoader &loader, IWriter &writer)
{
    auto tree = internal::createtree(loader);
    auto codes = internal::treetotable(tree);
    deletetree(tree);
    writetable(writer, codes);
    loader.seek(0);
    uint_fast8_t bytepos = 0;
    byte currentwrite = 0;
    while (!loader.end())
    {
        byte current = loader.get();
        auto x = codes[current];
        writecodedbyte(x, bytepos, writer, currentwrite);
    }
    writecodedbyte(codes[internal::eof], bytepos, writer, currentwrite);
    writer.write(currentwrite);
}

namespace huffman::internal {

void writetable(IWriter &writer, codetable codes)
{
    byte codesize[2];
    chunk bincode;
    //0. Number of elements, in uint16le
    uint16_t num = 0;
    for (auto i : codes)
    {
        if (i.bitsize != 0)
        num++;
    }
    byte numbytes[2];
    splituint16(num, numbytes);
    writer.write(numbytes[0]);
    writer.write(numbytes[1]);
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
            bincode = getbinarycode(codes[i]);
            writer.writeChunk(bincode);
        }
        if (i == 255)
            break;
    }
}
chunk getbinarycode(code code)
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