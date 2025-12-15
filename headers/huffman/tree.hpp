#pragma once
#include "data.hpp"
#include "loader.hpp"
#include "huffman.hpp"
#include <array>
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
    bool operator() (node *a, node *b)
    {
        //we need lowest first
        return a->count > b->count;
    }
};

node* createtree(ILoader &loader);

void debugprintree(node* root);

void deletetree(node* top);

}