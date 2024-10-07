#pragma once

#include <iostream>

class DisjointSet {    // 不相交集
private:
    int size;      // 大小
    int *parent;   // 数组存储

public:
    DisjointSet(int s);
    ~DisjointSet() {delete[] parent;}
    int Find(int x);
    void Union(int root1, int root2);
    bool connected(int v1, int v2);
};

inline DisjointSet::DisjointSet(int s) 
{
    size = s;
    parent = new int[size];
    for (int i=0; i<size; i++) {
        parent[i] = -1;
    }
} 

inline bool DisjointSet::connected(int v1, int v2)
{
    return Find(v1) == Find(v2);
}

inline int DisjointSet::Find(int x)
{
    if (parent[x] < 0) return x;
    return parent[x] = Find(parent[x]);
}

inline void DisjointSet::Union(int v1, int v2)
{
    // v1 v2 可为任意结点
    // v1 与 v2 子节点个数相同时，v1成为v2的子节点
    if (v1 == v2) return;

    int rootOfv1 = Find(v1);
    int rootOfv2 = Find(v2);
    if (rootOfv1 == rootOfv2) return;

    int sizeOfv1 = -parent[rootOfv1];
    int sizeOfv2 = -parent[rootOfv2];

    if (sizeOfv1 > sizeOfv2) {
        parent[rootOfv1] += parent[rootOfv2];
        parent[rootOfv2] = rootOfv1;
    } else {
        parent[rootOfv2] += parent[rootOfv1];
        parent[rootOfv1] = rootOfv2;
    }
}

