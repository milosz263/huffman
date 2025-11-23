#include "data.hpp"

std::vector<std::byte> loadFile(std::string filename)
{
    fs::path path(filename);
    std::vector<std::byte> file;
    file.reserve(fs::file_size(path));
    std::ifstream input;
    input.open(path, std::ios::binary);
    return file;
}