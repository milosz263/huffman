#pragma once
#include "data.hpp"
#include "loader.hpp"
#include "writer.hpp"
#include "huffman/internal.hpp"
#include <array>
#include <bitset>
#include <unordered_map>

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
    static bool operator() (const node *a, const node *b);
};


node* createtree(ILoader &loader);

void deletetree(node* top);

struct code
{
    std::bitset<257> data;
    uint16_t bitsize = 0;
};

class codecmp
{
    public:
    static bool operator() (const code &a, const code &b);
};

class codehash
{
    public:
    static bool operator() (const code& c);
};


typedef std::array<code, 257> codetable;

codetable treetotable(node* root);

code addbit(code code, byte bit);

void writetable(IWriter &writer, codetable codes);

chunk getbinarycode(code code);

typedef std::unordered_map<code, hval, codehash, codecmp> codemap; 

}