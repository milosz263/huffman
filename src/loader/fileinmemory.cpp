#include "loader/fileinmemory.hpp"
#include <fstream>
#include <cassert>

FileInMemoryLoader::FileInMemoryLoader(fs::path path)
{
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
    if (_pos == _data.size())
        throw LoaderPositionException();
    return _data[_pos++];
}

chunk FileInMemoryLoader::getChunk(size_t maxSize)
{
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
    if (_data.size()<=pos)
        throw LoaderPositionException();
    _pos = pos;
}

size_t FileInMemoryLoader::pos()
{
    return _pos;
}

size_t FileInMemoryLoader::size()
{
    return _data.size();
}
