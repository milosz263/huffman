#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include <cstdint>
/**
 * @brief Typedef to uint8_t.
 * @note Using uint8 instead of std::byte will be simpler for this use case.
 * 
 */
typedef uint8_t byte;

#include <vector>
/**
 * @brief Typedef to std::vector<byte>.
 * 
 */
typedef std::vector<byte> chunk;