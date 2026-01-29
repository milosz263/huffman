/**
 * @file huffman.hpp
 * @brief 
 * 
 */
#pragma once
#include "loader.hpp"
#include "writer.hpp"
#include <exception>


namespace huffman
{
    void Encode(ILoader &loader, IWriter &writer);
    void Decode(ILoader &loader, IWriter &writer);

    class UnsupportedFileException : public std::exception
    {};
    
}