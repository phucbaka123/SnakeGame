#ifndef NODE_H
#define NODE_H

template<typename T>
struct Node {
    T data;
    Node* next;

    Node(T value);
};
#include "Node.cpp"
#endif