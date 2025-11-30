#include "writer/tofile.hpp"

ToFileWriter::ToFileWriter(fs::path path)
{
    _closed = false;
    _file.exceptions(std::ios::failbit | std::ios::badbit);
    _file.open(path, std::ios::binary | std::ios::trunc);
}

void ToFileWriter::write(byte b)
{
    _tryClosed();
    //why basic_i/ofstream is a template when it fails on something as simple as typedef'd unsigned char?
    _file.put(*reinterpret_cast<char*>(&b));
}

void ToFileWriter::writeChunk(chunk c)
{
    _tryClosed();
    //why basic_i/ofstream is a template when it fails on something as simple as typedef'd unsigned char?
    _file.write(reinterpret_cast<char*>(c.data()), c.size());
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