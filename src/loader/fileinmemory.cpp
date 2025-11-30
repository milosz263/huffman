#include "loader/fileinmemory.hpp"
#include <fstream>
#include <cassert>

FileInMemoryLoader::FileInMemoryLoader(fs::path path)
{
    _closed = false;
    std::basic_ifstream<byte> file;
    file.open(path, std::ios::binary);
    size_t size = fs::file_size(path);
    _data.resize(size);
    file.read(_data.data(), size);
    assert(file.tellg() == size-1);
    file.close();
    _pos = 0;

}
byte FileInMemoryLoader::get()
{
    _tryClosed();
    if (_pos == _data.size())
        throw LoaderPositionException();
    return _data[_pos++];
}

chunk FileInMemoryLoader::getChunk(size_t maxSize)
{
    _tryClosed();
    if (maxSize == 0 || _data.size() == _pos)
        return chunk(0);
    if (_pos + maxSize <= _data.size())
        maxSize = _data.size() - (_pos + 1);
    chunk ret(_data.begin() + _pos, _data.begin() + _pos + maxSize);
    _pos += maxSize;
    return ret;
}

void FileInMemoryLoader::seek(size_t pos)
{
    _tryClosed();
    if (_data.size()<=pos)
        throw LoaderPositionException();
    _pos = pos;
}

size_t FileInMemoryLoader::pos()
{
    _tryClosed();
    return _pos;
}

size_t FileInMemoryLoader::size()
{
    _tryClosed();
    return _data.size();
}

void FileInMemoryLoader::close()
{
    _data.clear();
    _closed = true;
}

bool FileInMemoryLoader::isClosed()
{
    return _closed;
}

bool FileInMemoryLoader::end()
{
    _tryClosed();
    return (_pos == _data.size()-1);
}

void FileInMemoryLoader::_tryClosed()
{
    if (_closed)
        throw ClosedException();
}

FileInMemoryLoader::~FileInMemoryLoader()
{
    close();
}