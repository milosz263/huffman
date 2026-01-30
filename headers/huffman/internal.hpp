/**
 * @file huffman/internal.hpp
 * Internal file
 */
#pragma once
#include "data.hpp"
#include <cstdint>

/**
 * @brief Namespace for things used by huffman::Encode() and huffman::Decode().
 * 
 */
namespace huffman::internal
{
    /**
     * @brief typedef to uint16_t.
     */
    typedef uint16_t hval;
    /**
     * @brief End of File node.
     * 
     */
    constexpr hval eof = 256;
    /**
     * @brief Empty node connecting others.
     * 
     */
    constexpr hval empty = 257;
}