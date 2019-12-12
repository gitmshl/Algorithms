#pragma once

template<class T>
void mshl::avl_tree::rot_left(node<T>* v)
{
    if (!v || !v->right) return;
    node* r = v->right;
    {
        node* p = v->parent;
        r->parent = p;
        if (p)
        {
            if (p->left == v) p->left = r;
            else p->right = r;
        }
    }
    node* b = r->left;
    r->left = v;
    v->parent = r;
    v->right = b;
    if (b) b->parent = v;
    fix_heigth<T>(v);
    fix_heigth<T>(r);
}

template<class T>
void mshl::avl_tree::rot_right(node<T>* v)
{
    if (!v || !v->left) return;
    node* l = v->left;
    {
        node* p = v->parent;
        l->parent = p;
        if (p)
        {
            if (p->left == v) p->left = l;
            else p->right = l;
        }
    }
    node* b = l->right;
    l->right = v;
    v->parent = l;
    v->left = b;
    if (b) b->parent = v;
    fix_heigth<T>(v);
    fix_heigth<T>(l);
}

template<class T>
void mshl::avl_tree::balance(node<T>* v)
{
    if (!v) return;
    uint diff_ = diff(v);
    if (diff_ == 2)
    {
        if (diff(v->right) < 0) rot_right(v->right);
        rot_left(v);
    }
    else if (diff_ == -2)
    {
        if (diff(v->left) < 0) rot_left(v->left);
        rot_right(v);
    }
}


template<class T>
mshl::node<T>* mshl::avl_tree::insert(T key, node<T>* v, node<T>* parent)
{
    if (!v) return new node(key, parent);
    if (v->key == key) return v;
    node* newp = nullptr;
    if (v->key > key) {newp = (v->left = insert(key, v->left, v));}
    else {newp = (v->right = insert(key, v->right, v));}
    balance(v);
    return newp;
}


template<class T>
mshl::node<T>* mshl::avl_tree::insert(T key)
{
    node<T>* newp = insert(key, root, nullptr);
    root = root ? root : newp;
}