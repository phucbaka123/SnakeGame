#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"

template<typename T>
class LinkedList {
    private:
    Node<T>* head;
    int length;

    public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);

    T get(int index);
    void insert(int index, T value);
    int getLength();
    void remove(int index);
    void clear();

    ~LinkedList();
};

#include "LinkedList.cpp"

#endif