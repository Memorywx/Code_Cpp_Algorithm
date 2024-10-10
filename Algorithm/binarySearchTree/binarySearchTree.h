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
    SET<KEY, OTHER> find(const KEY &x, binaryNode *t) const;
    void insert(const SET<KEY, OTHER> &x, binaryNode *&t);
    void remove(const KEY &x, binaryNode *&t);
    void makeEmpty(binaryNode *t);

};
