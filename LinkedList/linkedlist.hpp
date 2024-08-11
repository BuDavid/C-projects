#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <iostream>

struct Node {
public:
    Node(int val) : value(val), next(nullptr) {}
public:
    int value;
    Node* next;
};

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& list) noexcept;
    ~LinkedList();
public:
    void clear();
    void push_back(int val);
    void print();
    void insert(int idx, int val);
    void erase(int idx);
    LinkedList& operator=(const LinkedList& other);
private:
    Node* head;
};

#endif  // LINKEDLIST_H_
