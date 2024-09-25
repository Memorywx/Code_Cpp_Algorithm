#pragma once

#include <iostream>
#include "bTree.h"
#include "../seqQueue/seqQueue.hpp"

template <typename T>
class binaryTree : public bTree<T> {
private:
    struct Node {             // 二叉树的结点类
        Node *left, *right;   // 结点的左、右儿子结点的地址
        T data;
        Node() : left(nullptr), right(nullptr) {}
        Node(T item, Node *L = nullptr, Node *R = nullptr) 
            : data(item), left(L), right(R) {} 
        ~Node() {}
    };
    Node* root;

public:
    binaryTree() : root(nullptr) {}
    binaryTree(T x) { root = new Node(x); }
    ~binaryTree();
    void clear();
    void createTree(T flag);
    bool isEmpty() const;
    T getRoot(T flag) const;      
    T lchild(T x, T flag) const;
    T rchild(T x, T flag) const;     
    void delLeft(T x);
    void delRight(T x);
    void preOrder() const;
    void midOrder() const;
    void postOrder() const;
    void levelOrder() const;
    T parent(T x, T flag) const { return flag; }  // 不在二叉链表中找父结点，直接返回flag

private:
    Node *find(T x, Node *t) const;
    void clear(Node *&t);       // 对指针的引用，直接改变指针本身
    void preOrder(Node *t) const;
    void midOrder(Node *t) const;
    void postOrder(Node *t) const;
};

template <typename T>
inline binaryTree<T>::~binaryTree()
{
    clear(root);
}


template <typename T>
inline void binaryTree<T>::clear(Node *&t)     // 私有函数 clear
{
    // 递归删除左右子树
    if (t == nullptr) return;
    clear(t->left);
    clear(t->right);
    delete t;
    t = nullptr;
}

template <typename T>
inline void binaryTree<T>::clear()
{
    clear(root);
}

template <typename T>
inline void binaryTree<T>::createTree(T flag)
{
    // 创建树，若输入值为flag，则表示创建空子结点
    seqQueue<Node *> que;
    Node *tmp;
    T x, ldata, rdata;

    std::cout << "输入根结点：";
    std::cin >> x;
    root = new Node(x);
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        std::cout << "\n输入" << tmp->data << "的两个子结点(" << flag << "表示空结点): ";
        std::cin >> ldata >> rdata;
        if (ldata != flag) que.enQueue(tmp->left = new Node(ldata));
        if (rdata != flag) que.enQueue(tmp->right = new Node(rdata));
    }
    std::cout << "create completed!\n";
}

template <typename T>
inline bool binaryTree<T>::isEmpty() const
{
    return root == nullptr;
}

template <typename T>
inline T binaryTree<T>::getRoot(T flag) const
{
    if (root == nullptr) return flag;
    return root->data;
}

template <typename T>
inline typename binaryTree<T>::Node *binaryTree<T>::find(T x, Node *t) const
{
    Node *tmp;
    if (t == nullptr) return nullptr;
    if (t->data == x) return t;
    if (tmp = find(x, t->left))        // 若找左找到了，则返回tmp; 
        return tmp;
    else return find(x, t->right);     // 找左没找到，找右边
}

template <typename T>
inline T binaryTree<T>::lchild(T x, T flag) const
{
    // 找结点x的左子结点值，若x不存在或x的左子结点不存在，则返回flag
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->left == nullptr) return flag;
    return tmp->left->data;
}

template <typename T>
inline T binaryTree<T>::rchild(T x, T flag) const
{
    // 找结点x的右子结点值，若x不存在或x的右子结点不存在，则返回flag
    Node *tmp = find(x, root);
    if (tmp == nullptr || tmp->right == nullptr) return flag;
    return tmp->right->data;
}

template <typename T>
inline void binaryTree<T>::delLeft(T x)
{
    // 删除结点x的左子树
    Node *tmp = find(x, root);
    if (tmp == nullptr) return;
    clear(tmp->left);
}

template <typename T>
inline void binaryTree<T>::delRight(T x)
{
    // 删除结点x的右子树
    Node *tmp = find(x, root);
    if (tmp == nullptr) return;
    clear(tmp->right);
}

template <typename T>
inline void binaryTree<T>::preOrder(Node *t) const     // 私有函数 preOrder
{
    // 前序遍历二叉树
    if (t == nullptr) return;
    std::cout << t->data << " ";
    preOrder(t->left);
    preOrder(t->right);
}

template <typename T>
inline void binaryTree<T>::preOrder() const
{
    std::cout << "前序遍历：";
    preOrder(root);
    std::cout << "\n";
}

template <typename T>
inline void binaryTree<T>::midOrder(Node *t) const    // 私有函数 midOrder
{
    // 中序遍历二叉树
    if (t == nullptr) return;
    midOrder(t->left);
    std::cout<< t->data << " ";
    midOrder(t->right);
}


template <typename T>
inline void binaryTree<T>::midOrder() const
{
    std::cout << "中序遍历：";
    midOrder(root);
    std::cout << "\n";
}

template <typename T>
inline void binaryTree<T>::postOrder(Node *t) const   // 私有函数postOrder
{
    if (t == nullptr) return;
    postOrder(t->left);
    postOrder(t->right);
    std::cout << t->data << " "; 
}

template <typename T>
inline void binaryTree<T>::postOrder() const
{
    std::cout << "后序遍历：";
    postOrder(root);
    std::cout << "\n";
}

template <typename T>
inline void binaryTree<T>::levelOrder() const
{
    seqQueue<Node *> que;
    Node *tmp;

    std::cout << "层次遍历：";
    if (root == nullptr) return;
    que.enQueue(root);

    while (!que.isEmpty()) {
        tmp = que.deQueue();
        std::cout << tmp->data << " ";
        if (tmp->left) que.enQueue(tmp->left);
        if (tmp->right) que.enQueue(tmp->right);
    }
    std::cout << "\n";
}





