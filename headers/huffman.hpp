/**
 * @file huffman.hpp
 * @brief 
 * 
 */
#pragma once
#include "data.hpp"
#include "loader.hpp"
#include "writer.hpp"

namespace huffman
{
    void Encode(ILoader &loader, IWriter &writer);
    void Decode(ILoader &loader, IWriter &writer);
    namespace internal
    {
        typedef uint_fast16_t hval;
        constexpr hval eof = 256;
        constexpr hval empty = 257;
    }
}