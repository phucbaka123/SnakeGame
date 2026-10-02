#ifndef ARRAYLISTS_H
#define ARRAYLISTS_H

template<typename T>
class ArrayList {
    private:
    T* data;
    int length;
    int capacity;

    void resize(int newCapacity);

    public:
    ArrayList();
    ArrayList(int initialCapacity);

    ArrayList(const ArrayList& other);
    ArrayList& operator=(const ArrayList& other);

    void insert(int index, T value);
    bool remove(int index);
    T get(int index);
    int getLength();
    void clear();
    

    ~ArrayList();
};

#include "ArrayList.cpp"


#endif