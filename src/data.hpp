#pragma once

#include <vector>
#include <string>
#include <fstream>

#include <filesystem>
namespace fs = std::filesystem;

#include <cstddef>

/**
 * @todo finish implementation and documentation.
 * @brief 
 * 
 * @param filename 
 * @return std::vector<byte> 
 */
std::vector<std::byte> loadFile(std::string filename);