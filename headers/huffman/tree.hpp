#pragma once
#include "data.hpp"
#include "loader.hpp"

#include <array>
namespace huffman::internal {
/**
 * @brief Typedef to std::array<size_t, 256>
 * 
 */
typedef std::array<size_t, 256> bytecount;

/**
 * @brief Count how many of every byte are in data. Seeks loader to 0 at start.
 * 
 * @param loader ILoader
 * @return bytecount 
 */
bytecount CountBytes(ILoader &loader);
}