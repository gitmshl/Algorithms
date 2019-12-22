#pragma once

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::rot_left(mshl::node<T>* v)
{
    if (!v || !v->right) return v;
    node<T>* r = v->right;
    v->right = r->left;
    r->left = v;
    fix_heigth<T>(v);
    fix_heigth<T>(r);
    return r;
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::rot_right(mshl::node<T>* v)
{
    if (!v || !v->left) return v;
    node<T>* l = v->left;
    v->left = l->right;
    l->right = v;
    fix_heigth<T>(v);
    fix_heigth<T>(l);
    return l;
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::balance(mshl::node<T>* v)
{
    if (!v) return nullptr;
    fix_heigth(v);
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
    return v;
}


template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::insert(const T& key, mshl::node<T>* v)
{
    if (!v) return new node<T>(key);
    if (cmp(key, v->key)) v->left = insert(key, v->left);
    else if (cmp(v->key, key)) v->right = insert(key, v->right);
    else return v;
    return balance(v);
}

template<class T, typename Comparator>
void mshl::avl_tree<T, Comparator>::insert(const T& key)
{
    root = insert(key, root);
}


template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::min(node<T>* r) const
{
    if (!r) return nullptr;
    while (r->left) r = r->left;
    return r;
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::max(node<T>* r) const
{
    if (!r) return nullptr;
    while (r->right) r = r->right;
    return r;
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::find(const T& key, node<T>* r) const
{
    if (!r) return nullptr;
    while (r)
    {
        if (cmp(key, r->key)) r = r->left;
        else if (cmp(r->key, key)) r = r->right;
        else return r;
    }
    return nullptr;
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::min() const
{
    return min(root);
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::max() const
{
    return max(root);
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::find(const T& key) const
{
    return find(key, root);
}

template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::remove(const T& key, node<T>* r)
{
    if (!r) return nullptr;
    if (cmp(key, r->key)) r->left = remove(key, r->left);
    else if (cmp(r->key, key)) r->right = remove(key, r->right);
    else
    {
        node<T>* left = r->left;
        node<T>* right = r->right;
        delete r;
        if (!right) return left;
        node<T>* minim = min(right);
        minim->right = remove_min(right);
        minim->left = left;
        return balance(minim);
    }   
    return balance(r);
}

template<class T, typename Comparator>
void mshl::avl_tree<T, Comparator>::remove(const T& key)
{
    root = remove(key, root);
}


template<class T, typename Comparator>
mshl::node<T>* mshl::avl_tree<T, Comparator>::remove_min(node<T>* r)
{
    if (!r) return nullptr;
    if (!r->left) return r->right;
    r->left = remove_min(r->left);
    return balance(r);
}