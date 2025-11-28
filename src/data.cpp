#include "data.hpp"
#include <fstream>

class bytebuf : public std::basic_streambuf<byte>
{
public:
    bytebuf(std::vector<byte> v)
    {
        setbuf(v.data(), v.size());
    }
};

std::vector<byte> loadFile(std::string filename)
{
    fs::path path(filename);
    size_t size = fs::file_size(path);
    std::vector<byte> file;
    file.reserve(size);
    std::basic_ifstream<byte> input;
    input.open(path, std::ios::binary);
    input.read(file.data(), size);
    return file;
}

std::basic_istream<byte> vectorToIStream(std::vector<byte> vec)
{
    bytebuf buf(vec);
    return std::basic_istream<byte>(&buf);
}
