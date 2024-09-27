#pragma once

using namespace std;
template <typename T>
class hfTree {
private:
    struct Node
    {
        T data;   // 结点值
        int weight;   // 结点权值
        int parent, left, right;  // 父节点、左右子结点
    };
    Node *elem;
    int length;

public:
    struct hfCode
    {
        T data;         // 待编码字符
        string code;    // 哈夫曼编码
    };
    
    hfTree(const T *v, const int *w, int size);
    void getCode(hfCode result[]);
    ~hfTree() { delete[] elem; }
};

template <typename T>
inline hfTree<T>::hfTree(const T *v, const int *w, int size)
{
    const int MAX_INT = 32767;
    int min1, min2;            // 最小树、次最小树的权值
    int minIndex1, minIndex2;  // 最小树、次最小树的索引

    length = 2 * size;
    elem = new Node[length];
    for (int i=size; i<length; i++) {
        elem[i].data = v[i-size];
        elem[i].weight = w[i-size];
        elem[i].parent = elem[i].left = elem[i].right = 0;
    }
    for (int i=size-1; i>0; i--) {
        min1 = min2 = MAX_INT;
        minIndex1 = minIndex2 = 0;
        for (int j=i+1; j<length; j++) {
            if (elem[j].parent == 0) {
                if (elem[j].weight < min1) {
                    min2 = min1;
                    min1 = elem[j].weight;
                    minIndex2 = minIndex1;
                    minIndex1 = j;
                } else if(elem[j].weight < min2) {
                    min2 = elem[j].weight;
                    minIndex2 = j;
                }
            }
        }
        elem[i].weight = min1 + min2;
        elem[i].parent = 0;
        elem[i].left = minIndex1;
        elem[i].right = minIndex2;
        elem[minIndex1].parent = i;
        elem[minIndex2].parent = i;
    }
}

template <typename T>
inline void hfTree<T>::getCode(hfCode result[])
{
    int size = length / 2;
    int p, s;

    for (int i=size; i<length; i++) {
        result[i-size].data = elem[i].data;
        result[i-size].code = "";
        p = elem[i].parent;
        s = i;
        while(p) {
            if (elem[p].left == s) {
                result[i-size].code = '0' + result[i-size].code;
            } else {
                result[i-size].code = '1' + result[i-size].code;
            }
            s = p;
            p = elem[p].parent;
        }
    }
}
