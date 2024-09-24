#pragma once

#include <iostream>
#include "bTree.h"
#include "../seqQueue/seqQueue.hpp"

template <typename T>
class binaryTree : public bTree {
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