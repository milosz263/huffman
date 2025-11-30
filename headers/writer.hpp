/**
 * @file writer.hpp
 * @brief 
 */
#pragma once
#include "data.hpp"

/**
 * @brief Template class for writing data.
 */
class IWriter
{
public:
    /**
     * @brief Writes single byte.
     * @throws ClosedException
     * @param b byte to be written.
     */
    virtual void write(byte b) = 0;

    /**
     * @brief Writes chunk.
     * @throws ClosedException
     * @param c chunk to be written.
     */
    virtual void writeChunk(chunk c) = 0;

    /**
     * @brief Closes underlying buffer and blocks future writes.
     */
    virtual void close() = 0;

    /**
     * @brief Syncs underlying buffer.
     * @throws ClosedException
     */
    virtual void sync() = 0;

    /**
     * @brief Checks whether Writer is closed.
     * @return bool
     */
    virtual bool isClosed() = 0;

    /**
     * @brief Empty destructor.
     * @cite https://stackoverflow.com/a/318137
     */
    virtual ~IWriter(){}
};

class ToFileWriter;