#pragma once
#include "linkedlist.h"

template <typename T>
class HashMap {
    public:
    int size;
    LinkedList<T>* map;
    HashMap(int init_size = 0);
    int hash(T point);
    void insert(T point);
    bool search(T point);
    void clear();
};
