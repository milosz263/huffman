#include "writer/tofile.hpp"

ToFileWriter::ToFileWriter(fs::path path)
{
    _closed = false;
    _file.open(path, std::ios::binary | std::ios::trunc);
}

void ToFileWriter::write(byte b)
{
    _tryClosed();
    _file.put(b);
}

void ToFileWriter::writeChunk(chunk c)
{
    _tryClosed();
    _file.write(c.data(), c.size());
}

void ToFileWriter::close()
{
    if (_closed)
        return;
    _closed = true;
    _file.close();
}

void ToFileWriter::sync()
{
    _tryClosed();
    _file.flush();
}

bool ToFileWriter::isClosed()
{
    return _closed;
}

ToFileWriter::~ToFileWriter()
{
    close();
}

void ToFileWriter::_tryClosed()
{
    if (_closed)
        throw ClosedException();
}