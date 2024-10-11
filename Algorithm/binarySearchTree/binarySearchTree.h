#pragma once

#include "../dynamicSearchTable/dynamicSearchTable.h"

template <class KEY, class OTHER>
class binarySearchTree : public dynamicSearchTable<KEY, OTHER> {
private:
    struct binaryNode
    {
        SET<KEY, OTHER> data;
        binaryNode *left;
        binaryNode * right;

        binaryNode(const SET<KEY, OTHER> &thedata, binaryNode *l = nullptr, 
            binaryNode *r = nullptr) 
            : data(thedata), left(l), right(r) {}
    };

    binaryNode *root;

public:
    binarySearchTree();
    ~binarySearchTree();
    SET<KEY, OTHER> *find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);

private:
    SET<KEY, OTHER> *find(const KEY &x, binaryNode *t) const;
    void insert(const SET<KEY, OTHER> &x, binaryNode *&t);
    void remove(const KEY &x, binaryNode *&t);
    void makeEmpty(binaryNode *t);

};

template <class KEY, class OTHER>
inline binarySearchTree<KEY, OTHER>::binarySearchTree()
{
    root = nullptr;
}

template <class KEY, class OTHER>
inline binarySearchTree<KEY, OTHER>::~binarySearchTree()
{
    makeEmpty(root);
}


template <class KEY, class OTHER>
inline void binarySearchTree<KEY, OTHER>::makeEmpty(binaryNode *t)
{
    if (t == nullptr) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}


template <class KEY, class OTHER>
inline SET<KEY, OTHER> *binarySearchTree<KEY, OTHER>::find(const KEY &x) const
{
    return find(x, root);
}


template <class KEY, class OTHER>
inline SET<KEY, OTHER> *binarySearchTree<KEY, OTHER>::find(const KEY &x, binaryNode *t) const
{
    if (t == nullptr || t->data.key == x) return (SET<KEY, OTHER>*) t;
    if (x < t->data.key) return find(x, t->left);
    else return find(x, t->right); 
}


template <class KEY, class OTHER>
inline void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    insert(x, root);
}


template <class KEY, class OTHER>
inline void binarySearchTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, binaryNode *&t)
{
    if (t == nullptr) t = new binaryNode(x, nullptr, nullptr);
    else if (x.key < t->data.key) {
        insert(x, t->left);
    } else if (x.key > t->data.key) {
        insert(x, t->right);
    }
}


template <class KEY, class OTHER>
inline void binarySearchTree<KEY, OTHER>::remove(const KEY &x)
{
    remove(x, root);
}

template <class KEY, class OTHER>
inline void binarySearchTree<KEY, OTHER>::remove(const KEY &x, binaryNode *&t)
{
    // 寻找过程
    if (t == nullptr) return;
    if (x < t->data.key) remove(x, t->left);
    else if (x > t->data.key) remove (x, t->right);

    // 找到了
    // 两个子节点都存在的情况
    else if (t->left != nullptr && t->right != nullptr) {
        // 用右子树的最小结点替换
        binaryNode *tmp = t->right;
        while (tmp->left != nullptr) tmp = tmp->left;
        t->data = tmp->data;
        remove (t->data.key, t->right);      // 将结点tmp删除
    } else {
        // 一个子节点或为叶子节点的情况
        binaryNode *oldNode = t;
        t = (t->left != nullptr) ? t->left : t->right;
        delete oldNode; 
    }
} 