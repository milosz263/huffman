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
 * @brief Class generating hash
 * 
 */
class codehash
{
    public:
    static size_t operator() (const code& c);
};


typedef std::array<code, 257> codetable;

codetable treetotable(node* root);

code addbit(code code, byte bit);

void writetable(IWriter &writer, codetable codes);

chunk getbinarycode(code code);

/**
 * @brief 
 */
typedef std::unordered_map<code, hval, codehash, codecmp> codemap; 

}