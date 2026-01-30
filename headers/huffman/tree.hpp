/**
 * @file huffman/tree.hpp
 * Internal file.
 * 
 */
#pragma once
#include "data.hpp"
#include "loader.hpp"
#include "writer.hpp"
#include "huffman/internal.hpp"
#include <array>
#include <bitset>
#include <unordered_map>

namespace huffman::internal {
/**
 * @brief Struct representing node in Huffman tree.
 * Left element is 0, right element is 1.
 */
struct node
{
    size_t count;
    hval data;
    node* left;
    node* right;
};

/**
 * @brief Class used to compare count element from node in priority_queue.
 * 
 */
class nodecmp
{
    public:
    /**
     * @return a > b
     */
    static bool operator() (const node *a, const node *b);
};

/**
 * @brief Creates Huffman tree based by file.
 * Leaves loader at end.
 * @param loader ILoader
 * @return node* pointer to top element in tree.
 */
node* createtree(ILoader &loader);

/**
 * @brief Deletes tree recursively.
 * 
 * @param top node* pointer to top element in tree.
 */
void deletetree(node* top);

/**
 * @brief Struct representing single code by std::bitset and its size (uint16_t)
 * 
 */
struct code
{
    std::bitset<257> data;
    uint16_t bitsize = 0;
};

/**
 * @brief Class used to compare two code structs.
 */
class codecmp
{
    public:
     /**
     * @return a == b
     */
    static bool operator() (const code &a, const code &b);
};

/**
 * @brief Class generating hash.
 * 
 */
class codehash
{
    public:
    /**
     * @return size_t
     */
    static size_t operator() (const code& c);
};


/**
 * @brief typedef to array of 257 (256 charaters + end of file) code elements.
 * 
 */
typedef std::array<code, 257> codetable;

/**
 * @brief Converts Huffman table to codetable.
 * 
 * @param root node* pointer to top element in tree.
 * @return codetable 
 */
codetable treetotable(node* root);

/**
 * @brief Inserts next bit to code.
 * 
 * @param code 
 * @param bit byte, only least significant bit is used.
 * @return code with inserted bit.
 */
code addbit(code code, byte bit);

/**
 * @brief Writes codetable to file in binary format.
 *
 * Format:
 * 1. Number of elements, in uint16-le
 * 2. Section header: 00 01, or 256 in little endian
 * 3. code for end of file, without character:
 * 3a. [0-1] - code size (in bits, uint16-le)
 * 3b. [3+]  - code
 * 4. Rest of codes
 * 4a. [0]   - character
 * 4b. [2-3] - code size (in bits, uint16-le)
 * 4c. [4+]  - code
 * @param writer IWriter
 * @param codes codetable
 */
void writetable(IWriter &writer, codetable codes);

/**
 * @brief Converts code to binary.
 * 
 * @param code 
 * @return chunk 
 */
chunk getbinarycode(code code);

/**
 * @brief typedef to std::unordered_map with code as key and hval as value.
 */
typedef std::unordered_map<code, hval, codehash, codecmp> codemap; 

}
