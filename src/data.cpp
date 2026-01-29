#include "data.hpp"
#include <bit>
#include <type_traits>
#include <utility>
#include <cstring>
#include <climits>

static_assert(std::endian::native == std::endian::little || std::endian::native == std::endian::big, "Can't determine endianness of system.");
static_assert(CHAR_BIT == 8, "Systems that don't have 8 bits per byte are not supported.");

void splituint16(uint16_t val, byte* ret)
{
    ret[0] = val & 0x00ff;
    ret[1] = (val & 0xff00) >> 8;
    if constexpr (std::endian::native == std::endian::big)
    {
        std::swap(ret[0],ret[1]);
    }
}

uint16_t readuint16(byte* val)
{
    if constexpr (std::endian::native == std::endian::big)
    {
        std::swap(val[0],val[1]);
    }
    uint16_t ret = 0;
    std::memcpy(&ret, val, 2);
    return ret;
}
