#pragma once

#include <fstream>
#include "writer.hpp"

class ToFileWriter : public IWriter
{
public:
    ToFileWriter(fs::path path);
    void write(byte b) override;
    void writeChunk(chunk &c) override;
    void close() override;
    void sync() override;
    bool isClosed() override;
    ~ToFileWriter();
private:
    std::ofstream _file;
    bool _closed;
    void _tryClosed();
};