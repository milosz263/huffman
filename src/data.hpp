#pragma once

#include <filesystem>
namespace fs = std::filesystem;

#include <cstdint>
/**
 * @brief Using uint8 instead of std::byte will be simpler for this use case.
 * 
 */
typedef uint8_t byte;