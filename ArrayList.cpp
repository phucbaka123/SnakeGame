#include "ArrayList.h"

template<typename T>
ArrayList<T>::ArrayList() { 
    capacity = 10;
    length = 0;
    data = new T[capacity];
}

template<typename T>
ArrayList<T>::ArrayList(int initialCapacity) { 
    if(initialCapacity < 1){
        capacity = 1;
    } else {
        capacity = initialCapacity;
    }
    length = 0;
    data = new T[capacity];
}

template<typename T>
ArrayList<T>::ArrayList(const ArrayList& other) { 
    capacity = other.capacity;
    length = other.length;
    data = new T[capacity];
    for(int i = 0; i < length; i++){
        data[i] = other.data[i];
    }
}

template<typename T>
ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other){
    if(this == &other){
        return* this;
    }

    delete[] data;

    capacity = other.capacity;
    length = other.length;

    data = new T[capacity];
    for(int i = 0; i < length; i++){
        data[i] = other.data[i];
    }
    return* this;
}


template<typename T>
void ArrayList<T>::resize(int newCapacity) { 
    T* newData = new T[newCapacity];
    for(int i = 0; i < length; i++){
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

template<typename T>
void ArrayList<T>::insert(int index, T value) {
    if(index < 0 || index > length){
        throw std::out_of_range("Invalid index!");
    }
    if(length == capacity){
        resize(capacity * 2);
    }

    for(int i = length; i > index; i--){
        data[i] = data[i - 1];
    }

    data[index] = value;
    length++;
}

template<typename T>
bool ArrayList<T>::remove(int index){

    if(index < 0 || index >= length){
        throw std::out_of_range("Invalid index!");
    }

    for(int i = index; i < length - 1; i++){
        data[i] = data[i+1];
    }
    
    length--;
    return true;
}

template<typename T>
T ArrayList<T>::get(int index){
    if(index < 0 || index >= length){
        throw std::out_of_range("Invalid index!");
    }
    return data[index];
}   


template<typename T>
int ArrayList<T>::getLength(){
    return length;
} 

template<typename T>
void ArrayList<T>::clear(){
    length = 0;
}


template<typename T>
ArrayList<T>::~ArrayList() {
    delete[] data;
}

