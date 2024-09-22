#pragma once

#include "stack.h"

template <typename T>
class seqStack : public stack<T> {

public:
    seqStack(int initSize = 10);
    ~seqStack();
    bool isEmpty() const;
    void push(const T &x);
    T pop();
    T top() const;

private:
    T *elem;
    int maxSize;
    int top_p;
    void recap(int newSize);
};

template <typename T>
inline seqStack<T>::seqStack(int initSize)
{
    elem = new T[initSize];
    maxSize = initSize;
    top_p = -1;
}

template <typename T>
inline seqStack<T>::~seqStack()
{
    delete[] elem;
}

template <typename T>
inline bool seqStack<T>::isEmpty() const
{
    return top_p == -1;
}

template <typename T>
inline void seqStack<T>::push(const T &x)
{
    if (top_p == maxSize - 1) {
        recap(maxSize * 2);
    }
    elem[++top_p] = x;
}

template <typename T>
inline T seqStack<T>::pop()
{
    return elem[top_p--];
}

template <typename T>
inline T seqStack<T>::top() const
{
    return elem[top_p];
}

template <typename T>
inline void seqStack<T>::recap(int newSize)
{
    T *tmp = elem;
    elem = new T[newSize];
    for(int i=0; i<maxSize; i++) {
        elem[i] = tmp[i];
    }
    maxSize = newSize;
    delete[] tmp;
}
