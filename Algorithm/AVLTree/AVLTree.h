#pragma once

#include "../dynamicSearchTable/dynamicSearchTable.h"

template <class KEY, class OTHER>
class AVLTree :  dynamicSearchTable<KEY, OTHER> {
private:
    struct AVLNode
    {
        SET<KEY, OTHER> data;
        AVLNode *left;
        AVLNode *right;
        int height;
        
        AVLNode(const SET<KEY, OTHER> &x, AVLNode *l = nullptr,
        AVLNode *r = nullptr, int h=1)
         : data(x), left(l), right(r), height(h) {}
    };
    
    AVLNode *root;

public:
    AVLTree() { root = nullptr; }
    ~AVLTree() { makeEmpty(root); }
    SET<KEY, OTHER>* find(const KEY &x) const;
    void insert(const SET<KEY, OTHER> &x);
    void remove(const KEY &x);

private:
    SET<KEY, OTHER>* find(const KEY &x, AVLNode *t) const;
    void insert(const SET<KEY, OTHER> &x, AVLNode *&t);
    bool remove(const KEY &x, AVLNode *&t);
    void makeEmpty(AVLNode *t);
    int height(AVLNode *t) const {return t == nullptr ? 0 : t->height;}
    void LL(AVLNode *&t);
    void RR(AVLNode *&t);
    void LR(AVLNode *&t);
    void RL(AVLNode *&t);
    int max(int a, int b) {return (a > b) ? a : b;}
    bool adjust(AVLNode *&t, int subTree);
};

template <class KEY, class OTHER>
inline SET<KEY, OTHER> *AVLTree<KEY, OTHER>::find(const KEY &x) const
{
    return find(x, root);
}


template <class KEY, class OTHER>
inline SET<KEY, OTHER> *AVLTree<KEY, OTHER>::find(const KEY &x, AVLNode *t) const
{
    if (t == nullptr || t->data.key == x) return (SET<KEY, OTHER>*) t;
    if (x < t->data.key) return find(x, t->left);
    else return find(x, t->right);
}

template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x)
{
    insert(x, root);
}


template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::insert(const SET<KEY, OTHER> &x, AVLNode *&t)
{
    if (t == nullptr) t = new AVLNode(x);
    else if (x.key < t->data.key) {
        // 在左子树插入
        insert(x, t->left);
        if (height(t->left) - height(t->right) == 2) {  // 检查是否失衡
            if (x.key < t->left->data.key) LL(t); else LR(t); 
        }
    }
    else if (x.key > t->data.key) {
        insert(x, t->right);
        if (height(t->right) - height(t->left) == 2) {
            if (x.key > t->right->data.key) RR(t); else RL(t);
        }
    }
         
    // 重新计算高度
    t->height = max(height(t->left), height(t->right)) + 1;
    
}


template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::makeEmpty(AVLNode *t)
{
    if (t == nullptr) return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
}

template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::LL(AVLNode *&t)
{
    AVLNode *t1 = t->left;
    t->left = t1->right;
    t1->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;
    t = t1;
}

template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::RR(AVLNode *&t)
{
    AVLNode *t1 = t->right;
    t->right = t1->left;
    t1->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    t1->height = max(height(t1->left), height(t1->right)) + 1;
    t = t1;
}

template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::LR(AVLNode *&t)
{
    RR(t->left);
    LL(t);
}

template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::RL(AVLNode *&t)
{
    LL(t->right);
    RR(t);
}

template <class KEY, class OTHER>
inline void AVLTree<KEY, OTHER>::remove(const KEY &x)
{
    remove(x, root);
}

template <class KEY, class OTHER>
inline bool AVLTree<KEY, OTHER>::remove(const KEY &x, AVLNode *&t)
{
    if (t == nullptr) return true;
    if (x == t->data.key) {
        if (t->left == nullptr || t->right == nullptr) {
            // 待删除结点是叶结点或只有一个子结点的结点
            AVLNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
            return false;
        }
        else {
            // 待删除结点有两个子结点
            AVLNode *t1 = t->right;
            while (t1->left != nullptr) t1 = t1->left;
            t->data = t1->data;
            if (remove(t1->data.key, t->right)) return true;
            return adjust(t, 1);
        }       
    }
    else if (x < t->data.key) {
        if (remove(x, t->left)) return true;
        return adjust(t, 0);
    }
    else {
        if (remove(x, t->right)) return true;
        return adjust(t, 1);
    }
       
}

template <class KEY, class OTHER>
inline bool AVLTree<KEY, OTHER>::adjust(AVLNode *&t, int subTree)
{
    // subTree == 1 代表右子树   subTree == 0 代表左子树
    if (subTree) {
        // 在右子树上删除
        if (height(t->left) - height(t->right) == 1) return true;
        if (height(t->left) == height(t->right)) {
            --t->height;
            return false;
        }
        if (height(t->left->right) > height(t->left->left)) {
            LR(t);
            return false;
        }
        LL(t);
        if (height(t->left) == height(t->right)) return false; else return true;
    }

        // 在左子树上删除
    else {
        // 情况1. t是平衡的
        if (height(t->right) - height(t->left) == 1) return true;
        // 情况2. t是左高右低的
        if (height(t->left) == height(t->right)){
            --t->height;
            return false;
        }
        // 情况3 t是右高左低的
        // 3.2 t的右子树是左高右低的
        if (height(t->right->left) > height(t->right->right)) {
            RL(t);
            return false;
        }
        RR(t);
        // 3.1 t的右子树是左低右高的(旋转后完全平衡，但高度减1) 或 平衡的(旋转后高度不变)
        if (height(t->left) == height(t->right)) return false; else return true;
    }
}
