#pragma once
#include <iostream>
#include "list.h"


template <class T>
class arrayList : public list<T>{

public:
    arrayList(int initCap = 8);
    arrayList(const arrayList<T>& s);
    ~arrayList() { delete[] data; }
    void clear() { size = 0; }
    int length() const { return size; }
    void add(T e);
    T visit(int i) const { return data[i]; }
    void setElem(int i, T e);
    int search(const T &e) const;
    void insert(int i, const T &x);
    void remove(int i);
    void traverse() const;


private:
    T* data;
    int capacity;  // 容量
    int size;      // 元素个数

    void recap(int newcap);
};

template <class T>
inline arrayList<T>::arrayList(int initCap)
{
    data = new T[initCap];
    capacity = initCap;
    size = 0;
}

template <class T>
inline arrayList<T>::arrayList(const arrayList<T> &s)
{
    capacity = s.capacity;
    size = s.size;
    data = new T[capacity];
    for (int i=0; i<size; i++) {
        data[i] = s.data[i];
    }
}

template <class T>
inline void arrayList<T>::add(T e)
{
    if (size == capacity) {
        recap(capacity * 2);
    }
    data[size] = e;
    size++;
}


template <class T>
inline void arrayList<T>::setElem(int i, T e)
{
    if (i < 0 || i >= size) {
        return;
    }
    data[i] = e;
}

template <class T>
inline int arrayList<T>::search(const T &e) const
{
    int i;
    for (i=0; i<size && data[i]!=e; i++);
    if (i == size) { return -1; }
    else { return i; }
}

template <class T>
inline void arrayList<T>::insert(int i, const T &x)
{
    if (i < 0 || i > size) {
        return;
    }
    if (size == capacity) {
        recap(capacity * 2);
    }
    for (int j=size; j>i; j--) {
        data[j] = data[j-1];
    }
    data[i] = x;
    size++;
}

template <class T>
inline void arrayList<T>::remove(int i)
{
    if (i < 0 || i >= size) {
        return;
    }
    for (int j=i; j<size-1; j++) {
        data[j] = data[j+1];
    }
    size--;
    if (size > 8 && size <= capacity / 4) {
        recap(capacity / 2);
    }
}

template <class T>
inline void arrayList<T>::traverse() const
{
    for (int i=0; i<size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << std::endl;
}

template <class T>
inline void arrayList<T>::recap(int newcap)
{
    T* tmp = data;
    data = new T[newcap];
    capacity = newcap;
    for (int i=0; i<size; i++) {
        data[i] = tmp[i];
    }
    delete[] tmp;
}
