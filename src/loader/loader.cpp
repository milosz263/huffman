#include "loader.hpp"
#include "loader/fileinmemory.hpp"

std::unique_ptr<ILoader> getLoaderFromFile(fs::path path, LoaderType type)
{
    switch (type)
    {
        case LoaderType::FileInMemory:
        default:
            return std::make_unique<FileInMemoryLoader>(path);
            break;
    }
}
