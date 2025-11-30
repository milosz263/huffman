/**
 * @file data.hpp
 * @brief This header delcares types used throughout entire program and related to handling data.
 * 
 */
#pragma once

#include <exception>
/**
 * @brief Exception type thrown when trying to use closed Writer or Loader.
 * 
 */
class ClosedException : public std::exception
{};

#include <filesystem>
namespace fs = std::filesystem;

#include <cstdint>
/**
 * @brief Typedef to uint8_t.
 * Using uint8 instead of std::byte will be simpler for this use case.
 * 
 */
typedef uint8_t byte;

#include <vector>
/**
 * @brief Typedef to std::vector<byte>.
 * 
 */
typedef std::vector<byte> chunk;