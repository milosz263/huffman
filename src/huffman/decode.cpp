#include "huffman/tree.hpp"
#include "huffman.hpp"
#include "huffman/internal.hpp"
#include <cmath>

void huffman::Decode(ILoader &loader, IWriter &writer)
{
    using internal::code;
    internal::codemap map;
    byte bu16[2];
    uint16_t codesize;
    internal::hval ch;

    // A. Table
    // 0. Number of elements, in uint16-le

    bu16[0] = loader.get();
    bu16[1] = loader.get();
    uint16_t elems = readuint16(bu16);

    // 1. Section header: 00 01, or 256 in little endian
    if (loader.get() != 0)
        throw UnsupportedFileException();
    if (loader.get() != 1)
        throw UnsupportedFileException();
    // 2. code for end of file, without character
    if (elems == 0)
        throw UnsupportedFileException();
    code ceof = {};
    elems--;
    ch = internal::eof;
    bu16[0] = loader.get();
    bu16[1] = loader.get();
    codesize = readuint16(bu16);
    ceof.bitsize = 0;
    int_fast16_t bytesize = std::ceil(codesize / 8.0);
    for (int_fast16_t i = 0; i < bytesize; i++)
    {
        byte b = loader.get();
        for (int_fast8_t j = 0; j < 8 && ceof.bitsize < codesize; j++)
            ceof.data[ceof.bitsize++] = ((b >> j) & 1);
    }
    map.emplace(ceof, ch);
    // 3. Rest of codes, in format: [0] - character, [1-2] - code size (in bits, uint16-le), [3+] code, ...
    for (int_fast16_t i = 0; i < elems; i++)
    {
        code c = {};
        ch = loader.get();
        bu16[0] = loader.get();
        bu16[1] = loader.get();
        codesize = readuint16(bu16);
        c.bitsize = 0;
        int_fast16_t bytesize = std::ceil(codesize / 8.0);
        for (int_fast16_t i = 0; i < bytesize; i++)
        {
            byte b = loader.get();
            for (int_fast8_t j = 0; j < 8 && c.bitsize < codesize; j++)
                c.data[c.bitsize++] = ((b >> j) & 1);
        }
        map.emplace(c, ch);
    }
    {
        code c = {};
        byte b = loader.get();
        int_fast8_t i = 0;
        bool endfile = false;
        while (!endfile)
        {
            if (!(i < 8))
            {
                b = loader.get();
                i = 0;
            }
            
            for (; i < 8 && !endfile; i++)
            {
                c.data[c.bitsize++] = (b >> i) & 1;

                if (map.count(c) == 1)
                {
                    auto x = map[c];
                    if (x == internal::eof)
                    {
                        endfile = true;
                        break;
                    }
                    writer.write(x);
                    c.bitsize = 0;
                    c.data.reset();
                }
            }
        }
    }
}