#pragma once

#ifdef TEST
#include <iostream>
#endif

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
    inline uint height(node<T>* v)
    {
        return v ? v->height : 0;
    }

    template<class T>
    inline int diff(node<T>* v)
    {
        return v ? int(height(v->right)) - int(height(v->left)) : 0;
    }

    template<class T>
    inline void fix_heigth(node<T>* v)
    {
        if (!v) return;
        uint lefth = height(v->left), righth = height(v->right);
        v->height = (lefth > righth ? lefth : righth) + 1;
    }

    template <class T>
    class avl_tree
    {
    public:
        avl_tree() : root(nullptr) {}

        void insert(T key);
        void remove(T key);
        node<T>* find(T key);
        node<T>* min();
        node<T>* max();
#ifdef TEST
        void print(node<T>* r)
        {
            if (!r) return;
            std::cout << r->key << " ";
            print(r->left);
            print(r->right);
        }
        void print()
        {
            print(root);
            std::cout << "\n----------------------------" << std::endl;
        }
#endif  
    private:
        node<T>* rot_left(node<T>* v);
        node<T>* rot_right(node<T>* v);
        node<T>* balance (node<T>* v);
        node<T>* insert(T key, node<T>* v, node<T>* parent);
        node<T>* remove(T key, node<T>* r);
        node<T>* remove_min(node<T>* r);
        node<T>* min(node<T>* r);
        node<T>* max(node<T>* r);
        node<T>* find(T key, node<T>* r);

        node<T>* root;
    };
}

#include "avl_tree_imp.hpp"