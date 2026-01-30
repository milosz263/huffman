/**
 * @file loader/fileinmemory.hpp
 * Internal file.
 */
#pragma once

#include "loader.hpp"

/**
 * @brief Class that reads entire file to memory at start using std::ifstream.
 * @implements ILoader
 */
class FileInMemoryLoader : public ILoader
{
public:
    FileInMemoryLoader(fs::path path);
    byte get() override;
    chunk getChunk(size_t maxSize) override;
    void seek(size_t pos) override;
    size_t pos() override;
    size_t size() override;
    void close() override;
    bool isClosed() override;
    bool end() override;
    ~FileInMemoryLoader();
private:
    size_t _pos;
    chunk _data;
    bool _closed;
    void _tryClosed();
};