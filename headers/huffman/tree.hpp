#pragma once
#include "data.hpp"
#include "loader.hpp"
#include "huffman.hpp"
#include <array>
#include <unordered_map>
#include <bitset>

namespace huffman::internal {

struct node
{
    size_t count;
    hval data;
    node* left;
    node* right;
};

class nodecmp
{
    public:
    bool operator() (node *a, node *b)
    {
        //we need lowest first
        return a->count > b->count;
    }
};


node* createtree(ILoader &loader);

void deletetree(node* top);

struct code
{
    std::bitset<257> data;
    uint16_t bitsize = 0;
};

typedef std::array<code, 257> codetable;

codetable treetotable(node* root);

code addbit(code code, byte bit);

void writetable(IWriter &writer, codetable codes);

codetable readtable(IWriter &writer);

}