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

}