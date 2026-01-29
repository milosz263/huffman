#include "huffman/tree.hpp"
#include <algorithm>
#include <queue>
namespace huffman::internal {

bool nodecmp::operator()(const node *a, const node *b)
{
    //we need lowest first
    return a->count > b->count;
}

bool codecmp::operator()(const code &a, const code &b)
{
    return (a.bitsize == b.bitsize && a.data == b.data);
}

bool codehash::operator()(const code& c)
{
    auto a = std::hash<std::bitset<257>>{}(c.data);
    a ^= c.bitsize;
    return a;
}

node* createtree(ILoader &loader)
{
    size_t counter[256] = {};
    loader.seek(0);
    while (!loader.end())
    {
        counter[loader.get()]++;
    }
    std::priority_queue<node*, std::vector<node*>, nodecmp> queue;
    node* end = new node;
    end->data = eof;
    end->count = 1;
    end->left = nullptr;
    end->right = nullptr;
    queue.push(end);
    for (int_fast16_t i = 0; i < 256; i++)
    {
        if (counter[i] == 0)
            continue;
        node* n = new node;
        n->data = i;
        n->count = counter[i];
        n->left = nullptr;
        n->right = nullptr;
        queue.push(n);
    }
    while (queue.size() >= 2)
    {
        node* l = queue.top();
        queue.pop();
        node* r = queue.top();
        queue.pop();

        node* n = new node;
        n->data = empty;
        n->count = l->count + r->count;
        n->left = l;
        n->right = r;
        queue.push(n);
    }
    node* root = queue.top();
    queue.pop();
    return root;
}

void deletetree(node *top)
{
    if (top == nullptr)
        return;
    deletetree(top->left);
    deletetree(top->right);
    delete top;
}

//Don't need to expose recursion only params.
static void treetotable(node *root, codetable &tab, code c)
{
    if (root->data != empty)
    {
        tab[root->data] = c;
        return;
    }
    treetotable(root->left, tab, addbit(c, 0));
    treetotable(root->right, tab, addbit(c, 1));
}

codetable treetotable(node* root)
{
    codetable ret = {};
    code c;
    c.bitsize = 0;
    treetotable(root, ret, c);
    return ret;
}

code addbit(code code, byte bit)
{
    code.data[code.bitsize++] = bit;
    return code;
}
/**
 * @brief Not implemented
 * @todo Implement decoding based on tree instead of map
 */
node* buildtree(ILoader &loader)
{
    
}
}