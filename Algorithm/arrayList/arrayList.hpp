#pragma once
#include <iostream>

const int initcap = 5;

template <class T>
class arrayList {

public:
    arrayList();
    arrayList(const arrayList<T>& s);
    ~arrayList();
    int getSize() const;
    void add(T e);
    bool getElem(int i, T& e);
    bool setElem(int i, T e);
    int getNo(T e) const;
    bool insert(int i, T e);
    bool del(int i);
    void printList();


private:
    T* data;
    int capacity;  // 容量
    int size;      // 元素个数

    void recap(int newcap);
};


template <class T>
arrayList<T>::arrayList()
{
    capacity = initcap;
    data = new T[initcap];
    size = 0;
}

template <class T>
arrayList<T>::arrayList(const arrayList<T> &s)
{
    capacity = s.capacity;
    size = s.size;
    data = new T[capacity];
    for (int i=0; i < size; i++) {
        data[i] = s.data[i];
    }
}

template <class T>
arrayList<T>::~arrayList() { delete[] data; }

template <class T>
int arrayList<T>::getSize() const
{
    return size;;
}

template <class T>
void arrayList<T>::add(T e) {
    if (size == capacity) {
        recap(capacity * 2);
    }
    data[size] = e;
    size++;
}

template <class T>
bool arrayList<T>::getElem(int i, T &e)
{
    if (i < 0 || i >= size) {
        return false;
    }
    e = data[i];
    return true;
}

template <class T>
bool arrayList<T>::setElem(int i, T e)
{
    if (i < 0 || i >= size) {
        return false;
    }
    data[i] = e;
    return true;
}

template <class T>
int arrayList<T>::getNo(T e) const
{
    for (int i=0; i<size; i++) {
        if (data[i] == e) {
            return i;
        }
    }
    return -1;
}

template <class T>
bool arrayList<T>::insert(int i, T e)
{
    if (i < 0 || i > size) {
        return false;
    }
    if (size == capacity) {
        recap(capacity * 2);
    }
    for (int j=size; j>i; j--) {
        data[j] = data[j-1];
    }
    data[i] = e;
    size++;
    return true;

}

template <class T>
bool arrayList<T>::del(int i)
{
    if (i < 0 || i >= size) {
        return false;
    }
    for (int j=i; j<size-1; j++) {
        data[j] = data[j+1];
    }
    size--;
    if (size > initcap && size <= capacity/4) {
        recap(capacity / 2);
    }
    return true;
}

template <class T>
void arrayList<T>::printList()
{
    for (int i=0; i<size; i++) {
        std::cout << data[i] << " ";
    }
    std::cout << '\n';
}

template <class T>
void arrayList<T>::recap(int newcap) {
    if (newcap <= 0 ) return;
    T* newdata = new T[newcap];
    capacity = newcap;
    for (int i=0; i<size; i++) {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
}
