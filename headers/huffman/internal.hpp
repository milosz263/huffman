#pragma once
#include "data.hpp"
#include <cstdint>

namespace huffman::internal
{
    typedef uint16_t hval;
    constexpr hval eof = 256;
    constexpr hval empty = 257;
}