/**
 * @file huffman.hpp
 */
#pragma once
#include "loader.hpp"
#include "writer.hpp"
#include <exception>

/**
 * @brief Namespace containing encoding and decoding functions.
 * 
 */
namespace huffman
{
    /**
     * @brief Encode file in loader and save it to writer.
     * 
     * @param loader ILoader&
     * @param writer IWriter&
     */
    void Encode(ILoader &loader, IWriter &writer);

    /**
     * @brief Decode file in loader and save it to writer.
     * @todo Optimize, currently it's slower than Encode()
     * @throws UnsupportedFileException
     * 
     * @param loader ILoader&
     * @param writer IWriter&
     */
    void Decode(ILoader &loader, IWriter &writer);

    /**
     * @brief Exception type thrown when trying to decode unsupported or corrupted file.
     */
    class UnsupportedFileException : public std::exception
    {};
    
}