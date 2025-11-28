#pragma once

#include <vector>
#include <string>
#include <istream>

#include <filesystem>
namespace fs = std::filesystem;

#include <cstdint>
/**
 * @brief Using uint8 instead of std::byte will be simpler for this use case.
 * 
 */
typedef uint8_t byte;

/**
 * @brief Load entire contents of file to memory. 
 * 
 * @param filename 
 * @return std::vector<byte> 
 */
std::vector<byte> loadFile(std::string filename);

/**
 * @brief Converts vector to istream.
 * 
 * @param vec std::vector<byte>
 * @return std::basic_istream<byte> 
 */
std::basic_istream<byte> vectorToIStream(std::vector<byte> vec);