#pragma once

#include "../arrayList/list.h"
#include <iostream>

template <class T>
class slinkList : list<T> {

public:
    slinkList();
    ~slinkList();
    void clear();
    int length() const { return size; }
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    void addLast(T e);
    void setElem(int i, T e);
    void traverse() const;

private:
    struct node {
        T data;
        node *next;
        node(const T &x, node *n = nullptr) { data = x; next = n;}
        node() : next(nullptr) {}
        ~node() {};
    };
    node* head;
    int size;
    node* move(int i) const;

};

template <class T>
inline slinkList<T>::slinkList()
{
    head = new node;
    size = 0;
}

template <class T>
inline slinkList<T>::~slinkList()
{
    clear();
    delete head;
}

template <class T>
inline void slinkList<T>::clear()
{
    node* p = head->next;
    node* q;

    head->next = nullptr;
    while (p!=nullptr) {
        q = p->next;
        delete p;
        p = q;
    }
    size = 0;
}

template <class T>
inline void slinkList<T>::insert(int i, const T &x)
{
    if (i < 0 || i > size) {
        return;
    }
    node* p = move(i-1);
    p->next = new node(x, p->next);
    size++;
}

template <class T>
inline void slinkList<T>::remove(int i)
{   
    if (i < 0 || i>=size) {
        return;
    }
    node *pos, *delp;
    pos = move(i-1);
    delp = pos->next;
    pos->next = delp->next;
    delete delp;
    size--;
}

template <class T>
inline int slinkList<T>::search(const T &x) const
{
    node* p = head->next;
    int i = 0;
    while (p!=nullptr && p->data!=x) {
        p = p->next;
        i++;
    }
    if (p==nullptr) { return -1; }
    else { return i; }
}

template <class T>
inline T slinkList<T>::visit(int i) const
{
    return move(i)->data;
}

template <class T>
inline void slinkList<T>::addLast(T e)
{
    if (size == 0) {
        head->next = new node(e);   
    } else {
        node* p = move(size-1);
        p->next = new node(e);
    }
    size++;
}

template <class T>
inline void slinkList<T>::setElem(int i, T e)
{
    if (i < 0 || i >= size) {
        return;
    }
    node* p = move(i);
    p->data = e;
}

template <class T>
inline void slinkList<T>::traverse() const
{
    node* p = head->next;
    while(p != nullptr) {
        std::cout << p->data << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template <class T>
inline typename slinkList<T>::node* slinkList<T>::move(int i) const
{
    node* p = head;
    while (i >= 0) {
        p = p->next;
        i--;
    }
    return p;
}
