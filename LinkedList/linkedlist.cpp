#include "linkedlist.hpp"
LinkedList::LinkedList() : head(nullptr) {}

LinkedList::LinkedList(const LinkedList& other) {
    if (!other.head) {
        head = nullptr;
    } else {
        head = new Node(other.head -> value);
        Node* curr_this = head;
        Node* curr_other = other.head -> next;

        while (curr_other) {
            curr_this -> next = new Node(curr_other -> value);
            curr_this = curr_this -> next;
            curr_other = curr_other -> next;
        }
    }
}

LinkedList::LinkedList(LinkedList&& other) noexcept {
    head = other.head;
    other.head = nullptr;
}

LinkedList& LinkedList::operator=(const LinkedList& other) {
    if (this == &other) {
        return *this;
    } else {
        clear();
        LinkedList tmp(other);
        std::swap(tmp.head, this -> head);
        return *this;
    }
}

void LinkedList::insert(int idx, int val) {
    if (idx < 0) {
        return;
    }

    Node* new_node = new Node(val);

    if (idx == 0) {
        new_node -> next = head;
        head = new_node;
        return;
    }

    Node* curr = head;
    Node* prev = nullptr;
    int curr_idx = 0;

    while (curr && curr_idx < idx) {
        prev = curr;
        curr = curr -> next;
        curr_idx++;
    }

    prev -> next = new_node;
    if (!curr) {
        std::cout << "out of range, inserting at the end." << std::endl;
    } else {
        new_node -> next = curr;
    }
}

void LinkedList::erase(int idx) {
    if (!head || idx < 0) {
        return;
    }

    if (idx == 0) {
        Node* tmp = head;
        head = head -> next;
        delete tmp;
        return;
    }

    Node* curr = head;
    Node* prev = nullptr;
    int curr_idx = 0;

    while (curr && curr_idx < idx) {
        prev = curr;
        curr = curr -> next;
        curr_idx++;
    }

    if (!curr) {
        std::cout << "out of range." << std::endl;
        return;
    }

    prev -> next = curr -> next;
    delete curr;
}

void LinkedList::print() {
    Node* curr = head;
    while (curr) {
        std::cout << curr -> value << ' ';
        curr = curr -> next;
    }
    std::cout << std::endl;
}

void LinkedList::clear() {
    while (head) {
        Node* tmp = head;
        head = head -> next;
        delete tmp;
    }
}

void LinkedList::push_back(int val) {
    Node* new_node = new Node(val);
    if (!head) {
        head = new_node;
    } else{
        Node* curr = head;
        while (curr -> next) {
            curr = curr -> next;
        }
        curr -> next = new_node;
    }
}

LinkedList::~LinkedList() {
    clear();
}

int main() {
    LinkedList list;
    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    list.insert(10, 10);
    list.print();
}
