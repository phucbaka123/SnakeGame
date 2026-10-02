#include "LinkedLists.h"
#include <stdexcept>

template <typename T>
LinkedList<T>::LinkedList() {
    head = nullptr;
    length = 0;
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) {
    head = nullptr;
    length = 0;
    *this = other;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other){
    if(this == &other){
        return *this;
    }

    Node<T>* current = head;
    while(current != nullptr){
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;

    if(other.head != nullptr){
        head = new Node<T>(other.head->data);
        Node<T>* currentOther = other.head->next;
        Node<T>* current = head;

        while(currentOther!=nullptr){
            current->next = new Node<T>(currentOther->data);
            current = current->next;
            currentOther = currentOther->next;
        }
    }

    length = other.length;
    return * this;
}

template <typename T>
int LinkedList<T>::getLength() {
    return length;
}

template <typename T>
T LinkedList<T>::get(int index){
    if (index >= length || index < 0){ // the linkedlist start at 0
        throw std::out_of_range("Invalid index!");
    }
    Node<T>* current = head;
    for(int i = 0; i < index; i++){
        current = current->next;
    }
    return current->data;
}

template <typename T>
void LinkedList<T>::insert(int index, T value){
    if (index > length || index < 0){ // the linkedlist start at 0
        throw std::out_of_range("Invalid index!");
    }
    Node<T>* temp = new Node<T>(value);
    Node<T>* current = head;
    if(index == 0){
        temp->next = head;
        head = temp;
    } else {
        for(int i = 0; i < index - 1; i++){
            current = current->next;
        }
        temp->next = current->next;
        current->next = temp;
    }
    length++;
}

template <typename T>
void LinkedList<T>::remove(int index){

    if (index >= length || index < 0) {
        throw std::out_of_range("Invalid index!");
    }

    Node<T>* temp;
    if(index == 0){
        temp = head;
        head = head->next;
    } else {
        Node<T>* current = head;
        for(int i = 0; i < index - 1; i++){
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }
    length--;
    delete temp;
}


template<typename T>
LinkedList<T>::~LinkedList() {
    Node<T>* current = head;
    while(current != nullptr){
        Node<T>* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}