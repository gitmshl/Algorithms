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


template<class T>
mshl::node<T>* mshl::avl_tree<T>::min(node<T>* r)
{
    if (!r) return nullptr;
    while (r->left) r = r->left;
    return r;
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::max(node<T>* r)
{
    if (!r) return nullptr;
    while (r->right) r = r->right;
    return r;
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::find(T key, node<T>* r)
{
    if (!r) return nullptr;
    while (r)
    {
        if (r->key == key) return r;
        if (r->key > key) r = r->left;
        else r = r->right;
    }
    return nullptr;
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::min()
{
    return min(root);
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::max()
{
    return max(root);
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::find(T key)
{
    return find(key, find);
}

template<class T>
mshl::node<T>* mshl::avl_tree<T>::remove(T key, node<T>* r)
{
    if (!r) return nullptr;
    if (r->key > key) {r->left= remove(key, r->left); if (r->left) r->left->parent = r;}
    else if (r->key < key) {r->right = remove(key, r->right); if (r->right) r->right->parent = r;}
    else
    {
        node<T>* left = r->left;
        node<T>* right = r->right;
        delete r;
        if (left) left->parent = nullptr;
        if (right) right->parent = nullptr;
        if (!right) return left;
        node<T>* minim = min(right);
        minim->right = remove_min(right);
        minim->left = left;
        return balance(minim);
    }   
    return balance(r);
}

template<class T>
void mshl::avl_tree<T>::remove(T key)
{
    root = remove(key, root);
}


template<class T>
mshl::node<T>* mshl::avl_tree<T>::remove_min(node<T>* r)
{
    if (!r) return nullptr;
    if (!r->left) return r->right;
    r->left = remove_min(r->left);
    if (r->left) r->left->parent = r;
    return balance(r);
}