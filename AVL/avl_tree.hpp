#pragma once

namespace mshl
{
    typedef unsigned char uint;

    template<class T>
    struct node
    {
        explicit node(const T& key) 
            : key(key), left(nullptr), right(nullptr), height(1)
        {}

        T key;
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

    template <class T, typename Comparator = std::less<T>>
    class avl_tree
    {
    public:
        avl_tree() : root(nullptr), cmp(Comparator()) {}

        void insert(const T& key);
        void remove(const T& key);
        node<T>* find(const T& key) const;
        node<T>* min() const;
        node<T>* max() const;

    private:
        node<T>* rot_left(node<T>* v);
        node<T>* rot_right(node<T>* v);
        node<T>* balance (node<T>* v);
        node<T>* insert(const T& key, node<T>* v);
        node<T>* remove(const T& key, node<T>* r);
        node<T>* remove_min(node<T>* r);
        node<T>* min(node<T>* r) const;
        node<T>* max(node<T>* r) const;
        node<T>* find(const T& key, node<T>* r) const;

        node<T>* root;
        Comparator cmp;
    };
}

#include "avl_tree_imp.hpp"