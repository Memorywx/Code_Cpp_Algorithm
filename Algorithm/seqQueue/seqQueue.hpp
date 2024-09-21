#pragma once

#include "queue.h"

template <typename T>
class seqQueue : public queue<T> {

public:
    seqQueue(int initSize = 10);
    ~seqQueue();
    bool isEmpty() const;
    void enQueue(const T &x);
    T deQueue();
    T getHead() const;

private:
    T *elem;
    int maxSize;
    int front, rear;   // front+1指向的位置才是队首  (为了区分队列空与满的情况) 

    void recap(int newSize);
    bool isFull() const;
};

template <typename T>
inline seqQueue<T>::seqQueue(int initSize)
{
    elem = new T[initSize];
    maxSize = initSize;
    front = rear = 0;
}

template <typename T>
inline seqQueue<T>::~seqQueue()
{
    delete[] elem;
}

template <typename T>
inline bool seqQueue<T>::isEmpty() const
{
    return front == rear;
}

template <typename T>
inline void seqQueue<T>::enQueue(const T &x)
{
    if (isFull()) {
        recap(maxSize * 2);
    }
    rear = (rear + 1) % maxSize;
    elem[rear] = x;
}

template <typename T>
inline T seqQueue<T>::deQueue()
{
    front = (front + 1) % maxSize;
    return elem[front];
}

template <typename T>
inline T seqQueue<T>::getHead() const
{
    return elem[(front + 1) % maxSize];
}

template <typename T>
inline void seqQueue<T>::recap(int newSize)
{
    T *tmp = elem;
    elem = new T[newSize];
    for (int i=1; i<maxSize; i++) {
        elem[i] = tmp[(front + i) % maxSize];
    }
    front = 0;
    rear = maxSize - 1;
    maxSize = newSize;
    delete[] tmp;
}

template <typename T>
inline bool seqQueue<T>::isFull() const
{
    return (rear + 1) % maxSize == front;
}
