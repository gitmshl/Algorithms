#pragma once

template<class T>
mshl::node<T>* mshl::avl_tree<T>::rot_left(mshl::node<T>* v)
{
    std::cout << "rot left\n";
    if (!v || !v->right) return v;
    node<T>* r = v->right;
    {
        node<T>* p = v->parent;
        r->parent = p;
        if (p)
        {
            if (p->left == v) p->left = r;
            else p->right = r;
        }
    }
    node<T>* b = r->left;
    r->left = v;
    v->parent = r;
    v->right = b;
    if (b) b->parent = v;
    fix_heigth<T>(v);
    fix_heigth<T>(r);
    if (!r->parent) root = r;
    return r;
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::rot_right(mshl::node<T>* v)
{
    if (!v || !v->left) return v;
    node<T>* l = v->left;
    {
        node<T>* p = v->parent;
        l->parent = p;
        if (p)
        {
            if (p->left == v) p->left = l;
            else p->right = l;
        }
    }
    node<T>* b = l->right;
    l->right = v;
    v->parent = l;
    v->left = b;
    if (b) b->parent = v;
    fix_heigth<T>(v);
    fix_heigth<T>(l);
    if (!l->parent) root = l;
    return l;
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::balance(mshl::node<T>* v)
{
    if (!v) return nullptr;
    uint diff_ = diff(v);
    if (diff_ == 2)
    {
        if (diff(v->right) < 0) rot_right(v->right);
        return rot_left(v);
    }
    else if (diff_ == -2)
    {
        if (diff(v->left) < 0) rot_left(v->left);
        return rot_right(v);
    }
    fix_heigth(v);
    return v;
}


template<class T>
mshl::node<T>* mshl::avl_tree<T>::insert(T key, mshl::node<T>* v, mshl::node<T>* parent)
{
    if (!v) return new node<T>(key, parent);
    if (v->key == key) return v;
    if (v->key > key) v->left = insert(key, v->left, v);
    else v->right = insert(key, v->right, v);
    return balance(v);
}

template<class T>
void mshl::avl_tree<T>::insert(T key)
{
    node<T>* newp = insert(key, root, nullptr);
    root = root ? root : newp;
}