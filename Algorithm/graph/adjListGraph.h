/*
基于邻接表的图类
*/

#pragma once

#include "gragh.h"
#include "../seqQueue/seqQueue.hpp"


template <class TypeOfVer, class TypeOfEdge>
class adjListGraph : public graph<TypeOfVer, TypeOfEdge> {
public:
    adjListGraph(int vSize, const TypeOfVer d[]);
    void insert(TypeOfVer x, TypeOfVer y, TypeOfEdge w);
    void remove(TypeOfVer x, TypeOfVer y);
    bool exist(TypeOfVer x, TypeOfVer y) const;
    ~adjListGraph();
    void dfs() const;
    void bfs() const;
    void topSort() const;  // 拓扑排序
    void criticalPath() const;   // 关键路径

private:
    struct edgeNode
    {
        int end;        // 终点
        TypeOfEdge weight;   // 权值
        edgeNode *next;
        edgeNode(int e, TypeOfEdge w, edgeNode *n=nullptr) 
            : end(e), weight(w), next(n) {}
    };
    
    struct verNode
    {
        TypeOfVer ver;   // 顶点值
        edgeNode *head;
        verNode(edgeNode *h=nullptr) 
            :  head(h) {}
    };

    verNode *verList;    // 邻接表
    int find(TypeOfVer x) const {
        for (int i=0; i < this->Vers; ++i) {
            if (verList[i].ver == x)
                return i;
        }
        return -1;
    }
    void dfs(int start, bool visited[]) const;
    
};

template <class TypeOfVer, class TypeOfEdge>
inline adjListGraph<TypeOfVer, TypeOfEdge>::adjListGraph(int vSize, const TypeOfVer d[])
{
    this->Vers = vSize;
    this->Edges = 0;
    
    verList = new verNode[vSize];
    for (int i=0; i<vSize; ++i) verList[i].ver = d[i];
}


template <class TypeOfVer, class TypeOfEdge>
inline adjListGraph<TypeOfVer, TypeOfEdge>::~adjListGraph()
{
    edgeNode *p;
    for (int i = 0; i < this->Vers; ++i) {
        while ((p = verList[i].head) != nullptr) {
            verList[i].head = p->next;
            delete p;
        } 
    }
    delete []verList;
}



template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::insert(TypeOfVer x, TypeOfVer y, 
    TypeOfEdge w)
{
    int u = find(x); int v = find(y);
    verList[u].head = new edgeNode(v, w, verList[u].head);
    ++this->Edges;
}

template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::remove(TypeOfVer x, TypeOfVer y)
{
    edgeNode *p, *q;
    int u = find(x);
    int v = find(y);
    p = verList[u].head;
    if (p == nullptr) return;

    // 没有哨兵节点 需要分情况
    // 第一个结点就是要被删除的边
    if (p->end == v) {
        verList[u].head = p->next;
        delete p;
        --this->Edges;
        return;
    }

    // 查找后续连接的结点
    while (p->next != nullptr && p->next->end != v) p = p->next;
    if (p->next != nullptr) {
        q = p->next;
        p->next = q->next;
        delete q;
        --this->Edges;
    }
}

template <class TypeOfVer, class TypeOfEdge>
inline bool adjListGraph<TypeOfVer, TypeOfEdge>::exist(TypeOfVer x, TypeOfVer y) const
{
    int u = find(x);
    int v = find(y);
    edgeNode *p = verList[u].head;
    while (p != nullptr && p->end != v) p = p->next;
    if (p != nullptr) return true;
    else return false;
}


template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::dfs() const
{
    bool *visited = new bool[this->Vers];
    for (int i=0; i<this->Vers; ++i) visited[i] = false;

    std::cout << "当前图的dfs遍历序列为: " << '\n';
    for (int i=0; i<this->Vers; i++) {
        if (visited[i] == true) continue;
        dfs(i, visited);
        std::cout << '\n';
    }
}


template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::dfs(int start, bool visited[]) const
{
    edgeNode *p = verList[start].head;
    std::cout << verList[start].ver << '\t';
    visited[start] = true;
    while (p != nullptr) {
        if (visited[p->end] == false) 
            dfs(p->end, visited);
        p = p->next;
    }

}

template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::bfs() const
{
    bool *visited = new bool[this->Vers];
    int currentNode;
    seqQueue<int> que;
    edgeNode *p;
    for (int i=0; i<this->Vers; ++i) visited[i] = false;
    std::cout << "当前图的bfs遍历序列为: " << '\n';
    for (int i=0; i<this->Vers; ++i) {
        if (visited[i] == true) continue;
        que.enQueue(i);
        while (!que.isEmpty()) {
            currentNode = que.deQueue();
            if (visited[currentNode] == true) continue;
            std::cout << verList[currentNode].ver << '\t';
            visited[currentNode] = true;
            p = verList[currentNode].head;
            while (p != nullptr) {
                if (visited[p->end] == false) que.enQueue(p->end);
                p = p->next;
            }
        }
    }
    std::cout << '\n';
}

template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::topSort() const
{
    seqQueue<int> que;
    edgeNode* p;
    int current;
    int *inDegree = new int[this->Vers];
    for (int i=0; i<this->Vers; ++i) inDegree[i] = 0;
    for (int i=0; i<this->Vers; ++i) {
        p = verList[i].head;
        while (p != nullptr) {
            ++inDegree[p->end];
            p = p->next;
        }
    }
    for (int i=0; i<this->Vers; ++i) {
        if (inDegree[i] == 0) {
            que.enQueue(i);
        }
    }
    std::cout << "拓扑排序为: " << '\n';
    while (!que.isEmpty()) {
        current = que.deQueue();
        std::cout << verList[current].ver << '\t';
        for (p = verList[current].head; p != nullptr; p = p->next) {
            if (--inDegree[p->end] == 0) {
                que.enQueue(p->end);
            }
        }
    }
    std::cout << '\n';
}

template <class TypeOfVer, class TypeOfEdge>
inline void adjListGraph<TypeOfVer, TypeOfEdge>::criticalPath() const
{
    TypeOfEdge* ee = new TypeOfEdge[this->Vers];   // 最早发生时间序列
    TypeOfEdge* le = new TypeOfEdge[this->Vers];   // 最晚发生时间序列
    int* top = new int[this->Vers];   // 记录拓扑排序序列
    int* inDegree = new int[this->Vers];  // 记录每个节点的入度
    seqQueue<int> que;
    int i;
    edgeNode* p;

    for (i = 0; i < this->Vers; ++i) inDegree[i] = 0;
    for (i = 0; i < this->Vers; ++i) {
        for (p = verList[i].head; p != nullptr; p = p->next) {
            ++inDegree[p->end];
        }
    }
    // 将入度为0的入队
    for (i = 0; i < this->Vers; ++i) {
        if (inDegree[i] == 0) {
            que.enQueue(i);
        }
    }
    // 拓扑排序
    i = 0;
    while (!que.isEmpty()) {
        top[i] = que.deQueue();
        for (p = verList[top[i]].head; p != nullptr; p = p->next) {
            if (--inDegree[p->end] == 0) {
                que.enQueue(p->end);
            }
        }
        ++i;
    }

    // 找最早发生时间
    for (i = 0; i < this->Vers; ++i) ee[i] = 0;
    for (i = 0; i < this->Vers; ++i) {
        for (p = verList[top[i]].head; p != nullptr; p = p->next) {
            if (ee[p->end] < ee[top[i]] + p->weight) {
                ee[p->end] = ee[top[i]] + p->weight;
            }
        }
    }

    // 找最晚发生时间
    for (i = 0; i < this->Vers; ++i) le[i] = ee[top[this->Vers-1]];
    for (i = this->Vers - 1; i >=0; --i) {
        for (p = verList[top[i]].head; p != nullptr; p = p->next) {
            if (le[p->end] - p->weight < le[top[i]])  {
                le[top[i]] = le[p->end] - p->weight;
            }
        }
    }

    // 找出关键路径
    for (i = 0; i < this->Vers; ++i) {
        if (ee[top[i]] == le[top[i]]) {
            std::cout << '(' << verList[top[i]].ver << ',' << ee[top[i]] << ')';
        }
    }
    std::cout << '\n';
}
