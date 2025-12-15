#include "huffman/tree.hpp"
#include <algorithm>
#include <queue>
namespace huffman::internal {

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
        end->data = i;
        end->count = counter[i];
        end->left = nullptr;
        end->right = nullptr;
        queue.push(n);
    }
    while (queue.size() >= 2)
    {
        node* l = queue.top();
        queue.pop();
        node* r = queue.top();
        queue.pop();

        node* n = new node;
        end->data = empty;
        end->count = l->count + r->count;
        end->left = l;
        end->right = r;
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

void treetotable(node *root, codetable &tab, code c)
{
    if (root->data != empty)
    {
        tab[root->data] = c;
        return;
    }
    treetotable(root->left, tab, addbit(c, 0));
    treetotable(root->right, tab, addbit(c, 1));
}

code addbit(code code, byte bit)
{
    code.data >>= 1;
    code.bitsize++;
    code.data[0] = bit;
    return code;
}

void writetable(IWriter &writer, codetable codes)
{
    //1. Section header: 00 01, or 256 in little endian
    writer.write(0);
    writer.write(1);
    //2. code for end of file, without character
    
    //3. Rest of codes, in format: [0] - character, [1-2] - code size (in bits, uint16-le), [3+] code, ...

}
}