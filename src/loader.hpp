#pragma once
#include "data.hpp"

struct chunk
{
    byte* data;
    size_t size;
};

class ILoader
{
public:
    virtual byte Get() = 0;
    virtual chunk GetChunk(size_t maxSize) = 0;
    virtual void Seek(size_t) = 0;
};