#pragma once

template <typename T>
class bTree {
public:
    virtual void clear() = 0;   // 清空树的结点
    virtual bool isEmpty() const = 0;   // 判断二叉树是否为空

    // 返回二叉树的根结点的值，若根结点不存在，则返回一个特殊值flag
    virtual T getRoot(T flag) const = 0;
    // 返回结点x的父结点的值，如果x是根结点，则返回一个特殊值flag
    virtual T parent(T x, T flag) const = 0;
    // 返回结点x的左子结点的值，如果x是根结点，则返回一个特殊值flag
    virtual T lchild(T x, T flag) const = 0;
    // 返回结点x的右子结点的值，如果x是根结点，则返回一个特殊值flag
    virtual T rchild(T x, T flag) const = 0;

    virtual void delLeft(T x) = 0;          // 删除结点x的左子树
    virtual void delRight(T x) = 0;         // 删除结点x的右子树
    virtual void preOrder() const = 0;      // 前序遍历
    virtual void midOrder() const = 0;      // 中序遍历
    virtual void postOrder() const = 0;     // 后序遍历
    virtual void levelOrder() const = 0;      // 层次遍历
    virtual ~bTree() {}
};