#pragma once

template <typename T> 
class Node {
    public:
        T val;
        Node<T>* next;
        Node(T init_val)
};

template <typename T> 
class LinkedList {
    public:
        Node<T>* head;
        Node<T>* tail;
        int size;
        LinkedList();
        void insert(T val);
        bool search(T val);
        void clear();
};