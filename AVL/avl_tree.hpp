#pragma once

namespace mshl
{
    typedef unsigned char uint;

    template<class T>
    struct node
    {
        explicit node(T key, node* parent = nullptr) 
            : key(key), parent(parent), left(nullptr), right(nullptr), height(1)
        {}

        T key;
        node* parent;
        node* left;
        node* right;
        uint height;
    };

    template<class T>
    inline uint height(node<T>* p)
    {
        return p ? p->height : 0;
    }

    template<class T>
    inline int diff(node<T>* p)
    {
        return p ? height(p->left) - height(p->right) : 0;
    }

    template<class T>
    inline void fix_heigth(node<T>* p)
    {
        if (!p) return;
        uint lefth = height(p->left), righth = height(p->right);
        p->height = (lefth > righth ? lefth : righth) + 1;
    }

    template <class T>
    class avl_tree
    {
    public:
        avl_tree() : root(nullptr) {}

    private:
        node<T>* root;
    };
}

#include "avl_tree_imp.hpp"