/**
 * @file huffman.hpp
 * @brief 
 * 
 */
#pragma once
#include "data.hpp"
#include "loader.hpp"
#include "writer.hpp"

namespace huffman
{
    void Encode(ILoader &loader, IWriter &writer);
    void Decode(ILoader &loader, IWriter &writer);
}