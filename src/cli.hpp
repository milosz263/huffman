#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Prints usage examples and list of switches to cerr.
 * 
 * @param exename name used as executable name in usage example.
 */
void printUsage(std::string exename);