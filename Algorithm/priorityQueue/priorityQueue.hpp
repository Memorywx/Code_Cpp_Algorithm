#pragma once

#include "../seqQueue/queue.h"

template <typename T>
class priorityQueue : public queue<T>{
private:
    T *elem;           // 最小堆
    int currentSize;   // 队列长度
    int maxSize;       // 

public:
    priorityQueue(int capacity = 100);
    priorityQueue(const T data[], int size);
    ~priorityQueue();
    void enQueue(const T &x);
    T getHead() const;
    T deQueue();
    bool isEmpty() const;
    void printTest();

private:
    void recap(int newSize);
    void buildHeap();
    void percolateDown(int hole);
};

template <typename T>
inline priorityQueue<T>::priorityQueue(int capacity)
{
    maxSize = capacity;
    currentSize = 0;
    elem = new T[capacity];
}


template <typename T>
inline priorityQueue<T>::~priorityQueue()
{
    delete[] elem;
}

template <typename T>
inline void priorityQueue<T>::enQueue(const T &x)
{
    if (currentSize == maxSize-1) recap(maxSize * 2);

    // 向上过滤
    int hole = ++currentSize;
    for (; hole > 1 && x < elem[hole / 2]; hole /= 2) {
        elem[hole] = elem[hole / 2]; 
    }
    elem[hole] = x;
}

template <typename T>
inline T priorityQueue<T>::getHead() const
{
    return elem[1];
}

template <typename T>
inline T priorityQueue<T>::deQueue()
{
    T minItem = elem[1];
    elem[1] = elem[currentSize--];
    percolateDown(1);         // 向下过滤
    return minItem;
}

template <typename T>
inline bool priorityQueue<T>::isEmpty() const
{
    return currentSize == 0;
}

template <typename T>
inline void priorityQueue<T>::printTest()
{
    for (int i=1; i<=currentSize; i++) {
        std::cout << elem[i] << " ";
    }
    std::cout << "\n";
}

template <typename T>
inline void priorityQueue<T>::recap(int newSize)
{
    T *tmp = elem;
    elem = new T[newSize];
    maxSize = newSize;
    for (int i=0; i<=currentSize; i++) {
        elem[i] = tmp[i];
    }
    delete[] tmp;
}

template <typename T>
inline void priorityQueue<T>::buildHeap()
{
    for (int i=currentSize/2; i>0; i--) {
        percolateDown(i);
    }
}

template <typename T>
inline void priorityQueue<T>::percolateDown(int hole)
{
    int child;
    T tmp = elem[hole];
    // 向下过滤
    for (; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && elem[child + 1] < elem[child]) {
            child++;
        }
        if (elem[child] < tmp) {
            elem[hole] = elem[child];
        } else {
            break;
        }
    }
    elem[hole] = tmp;
}

template <typename T>
inline priorityQueue<T>::priorityQueue(const T data[], int size)
    : maxSize(size + 10), currentSize(size)
{
    elem = new T[maxSize];
    for (int i=0; i<size; i++) elem[i+1] = data[i];
    buildHeap();
}
