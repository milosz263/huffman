/**
 * @file loader.hpp
 * @todo Add Loader implementations that don't read entire file to memory.
 */
#pragma once
#include <exception>
#include <memory>
#include "data.hpp"

/**
 * @brief Exception type thrown when trying to access invalid postion.
 * 
 */
class LoaderPositionException : public std::exception
{};

/**
 * @brief Enum with all implementations of ILoader.
 * 
 */
enum class LoaderType
{
    FileInMemory
};

/**
 * @brief Template class for loading data.
 */
class ILoader
{
public:
    /**
     * @brief Reads next byte.
     * 
     * @return byte 
     */
    virtual byte get() = 0;

    /**
     * @brief Reads next maxSize bytes.
     * @note If underlying data ends before maxSize then reads until end.
     * @param maxSize size_t
     * @return chunk 
     */
    virtual chunk getChunk(size_t maxSize) = 0;

    /**
     * @param pos size_t
     * @note if pos is invalid, then seeks to start (0).
     */
    virtual void seek(size_t pos) = 0;

    /**
     * @brief Gets current position.
     * 
     * @return size_t 
     */
    virtual size_t pos() = 0;

    /**
     * @brief Gets size of underlying data.
     * 
     * @return size_t 
     */
    virtual size_t size() = 0;

    /**
     * @brief Check if at the end of underlying data.
     * @note Only non-virtual function in ILoader.
     */
    bool end();

    /**
     * @brief Empty destructor.
     * @cite https://stackoverflow.com/a/318137
     */
    virtual ~ILoader(){}
};

/**
 * @brief Gets ILoader object.
 * 
 * @param path fs::path
 * @param type Defaults to FileInMemoryLoader if invalid (not file based loader or none specified).
 * @return Instance of class implementing ILoader.
 */
std::unique_ptr<ILoader> getLoaderFromFile(fs::path path, LoaderType type = LoaderType::FileInMemory);