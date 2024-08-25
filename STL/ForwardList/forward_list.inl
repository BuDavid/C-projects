#include "forward_list.hpp"

template <typename T>
ForwardList<T>::ForwardList() : m_head(nullptr) {}

template <typename T>
ForwardList<T>::ForwardList(const size_type size) : m_head(nullptr) {
    if (!size) {
        return;
    }
    m_head = new Node();
    Node* tmp = m_head;
    for (int i = 1; i < size; i++) {
        tmp -> next = new Node();
    }
}

template <typename T>
ForwardList<T>::ForwardList(const size_type size, const_reference value) : m_head(nullptr) {
    if (!size) {
        return;
    }
    m_head = new Node(value);
    Node* tmp = m_head;
    for (int i = 1; i < size; i++) {
        tmp -> next = new Node(value);
        tmp = tmp -> next;
    }
}

template <typename T>
ForwardList<T>::ForwardList(const std::initializer_list<T>& list) : m_head(nullptr) {
    if (!list.size()) {
        return;
    }

    auto it = list.begin();
    m_head = new Node(*it);
    Node* tmp = m_head;
    ++it;
    for (; it != list.end(); ++it) {
        tmp -> next = new Node(*it);
        tmp = tmp -> next;
    }
}

template <typename T>
ForwardList<T>::ForwardList(const ForwardList& other) : m_head(nullptr) {
    Node* other_tmp = other.m_head;
    if (!other_tmp) {
        return;
    }
    m_head = new Node(other_tmp -> val);
    Node* curr_tmp = m_head;
    while (other_tmp -> next) {
        other_tmp = other_tmp -> next;
        curr_tmp -> next = new Node(other_tmp -> val);
        curr_tmp = curr_tmp -> next;
    }
}

template <typename T>
ForwardList<T>::ForwardList(ForwardList&& other) {
    m_head = std::exchange(other.m_head, nullptr);
}

template <typename T>
ForwardList<T>::~ForwardList() {
    clear();
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const ForwardList& other) {
    if (this != &other) {
        ForwardList<T> tmp(other);
        *this = std::move(tmp);
    }
    return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(ForwardList&& other) noexcept {
    if (this != &other) {
        clear();
        m_head = std::exchange(other.m_head, nullptr);
    }
    return *this;
}

template <typename T>
ForwardList<T>& ForwardList<T>::operator=(const std::initializer_list<T>& list) {
    ForwardList<T> tmp(list);
    *this = std::move(tmp);
    return *this;
}

template <typename T>
bool ForwardList<T>::operator==(const ForwardList& other) const {
    if (this == &other) {
        return true;
    }

    Node* curr = m_head;
    Node* curr_other= other.m_head;

    while (curr && curr_other) {
        if (curr -> val != curr_other -> val) {
            return false;
        }
        curr = curr -> next;
        curr_other = curr_other -> next;
    }

    return !(curr || curr_other);
}

template <typename T>
bool ForwardList<T>::operator!=(const ForwardList& other) const {
    return !(*this == other);
}

template <typename T>
bool ForwardList<T>::operator>(const ForwardList& other) const {
    if (this == &other) {
        return false;
    }

    Node* curr = m_head;
    Node* curr_other= other.m_head;

    while (curr && curr_other) {
        if (curr -> val < curr_other -> val) {
            return false;
        }
        curr = curr -> next;
        curr_other = curr_other -> next;
    }

    return ((curr || curr_other) && !curr_other);
}

template <typename T>
bool ForwardList<T>::operator<(const ForwardList& other) const {
    return !(*this >= other);
}

template <typename T>
bool ForwardList<T>::operator>=(const ForwardList& other) const {
    return (other > *this || other == *this);
}

template <typename T>
bool ForwardList<T>::operator<=(const ForwardList& other) const {
    return (other < *this || other == *this);
}

template <typename T>
typename ForwardList<T>::reference ForwardList<T>::front() {
    return m_head -> val;
}

template <typename T>
typename ForwardList<T>::const_reference ForwardList<T>::front() const {
    return m_head -> val;
}

template <typename T>
bool ForwardList<T>::empty() const noexcept {
    return !m_head;
}

template <typename T>
typename ForwardList<T>::size_type ForwardList<T>::max_size() const noexcept {
    return std::numeric_limits<size_type>::max();
}

template <typename T>
void ForwardList<T>::clear() noexcept {
    while (m_head) {
        Node* tmp = m_head;
        m_head = m_head -> next;
        delete tmp;
    }
}
template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::begin() noexcept {
    return Iterator(m_head);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::end() noexcept {
    return Iterator(nullptr);
}

template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::begin() const noexcept {
    return ConstIterator(m_head);
}

template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::end() const noexcept {
    return ConstIterator(nullptr);
}

template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::cbegin() const noexcept {
    return ConstIterator(m_head);
}

template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::cend() const noexcept {
    return ConstIterator(nullptr);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::insert_after(ConstIterator pos, const_reference value) {
    Node* pos_node = const_cast<Node*>(pos.m_ptr);
    Node* new_node = new Node(value);

    new_node -> next = pos_node -> next;
    pos_node -> next = new_node;
    return Iterator(new_node);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::insert_after(ConstIterator pos, value_type&& value) {
    Node* pos_node = const_cast<Node*>(pos.m_ptr);
    Node* new_node = new Node(std::move(value));

    new_node -> next = pos_node -> next;
    pos_node -> next = new_node;
    return Iterator(new_node);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::insert_after(ConstIterator pos, size_type count, const_reference value) {
    Node* pos_node = const_cast<Node*>(pos.m_ptr);
    Node* rest = pos_node -> next;
    Node* tmp = pos_node;

    for (int i = 0; i < count; i++) {
        tmp -> next = new Node(value);
        tmp = tmp -> next; 
    }
    tmp -> next = rest;
    return Iterator(pos_node -> next);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::insert_after(ConstIterator pos, const std::initializer_list<T>& list) {
    Node* pos_node = const_cast<Node*>(pos.m_ptr);
    Node* rest = pos_node -> next;
    Node* tmp = pos_node;

    for (auto& elem : list) {
        tmp -> next = new Node(elem);
        tmp = tmp -> next; 
    }
    tmp -> next = rest;
    return Iterator(pos_node -> next);
}

template <typename T>
template <typename InputIt>
typename ForwardList<T>::Iterator ForwardList<T>::insert_after(ConstIterator pos, InputIt first, InputIt last) {
    Node* pos_node = const_cast<Node*>(pos.m_ptr);
    Node* rest = pos_node -> next;
    Node* tmp = pos_node;

    for (;first != last; ++first) {
        tmp -> next = new Node(*first);
        tmp = tmp -> next; 
    }

    tmp -> next = rest;
    return Iterator(pos_node -> next);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::erase_after(ConstIterator pos) {
    Node* pos_node = const_cast<Node*>(pos.m_ptr);

    Node* tmp = pos_node -> next;
    pos_node -> next = tmp -> next;
    delete tmp;

    return Iterator(pos_node);
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::erase_after(ConstIterator first, ConstIterator last) {
    Node* pos_node = const_cast<Node*>(first.m_ptr);
    Node* curr = pos_node -> next;

    while (curr != last.m_ptr) {
        Node* del_tmp = curr;
        curr = curr -> next;
        delete del_tmp;
    }

    pos_node -> next = const_cast<Node*>(last.m_ptr);
    return Iterator(pos_node);
}

template <typename T>
void ForwardList<T>::push_front(const_reference value) {
    Node* tmp = new Node(value);
    tmp -> next = m_head;
    m_head = tmp;
}

template <typename T>
void ForwardList<T>::push_front(value_type&& value) {
    Node* tmp = new Node(move(value));
    tmp -> next = m_head;
    m_head = tmp;
}

template <typename T>
void ForwardList<T>::pop_front() {
    if (m_head) {
        Node* tmp = m_head;
        m_head = m_head -> next;
        delete tmp;
    }
}

template <typename T>
void ForwardList<T>::resize(size_type count, const_reference value) {
    if (!count) {
        clear();
    }

    Node* curr = m_head;

    while (true) {
        if (!curr -> next) {
            break;
        }

        if (!(--count)) {
            break;
        }
        curr = curr -> next;
    }

    if (count == 1) {
        return;
    }

    if (!count) {
        Node* tmp = curr;
        curr = curr -> next;
        tmp -> next = nullptr;

        while (curr) {
            tmp = curr;
            curr = curr -> next;
            delete tmp;
        }
    } else {
        while (count != 1) {
            curr -> next = new Node(value);
            curr = curr -> next;
            count--;
        }
    }
}

template <typename T>
void ForwardList<T>::swap(ForwardList& other) noexcept {
    std::swap(m_head, other.m_head);
}

template <typename T>
void ForwardList<T>::merge(ForwardList& other) {
    if (this == &other) {
        return;
    }

    Node dummy = {};
    Node* curr = &dummy; 
    Node* other_head = other.m_head;
    Node* head = m_head;
    
    while (head && other_head) {
        if (head -> val < other_head -> val) {
            curr -> next = head;
            head = head -> next;
        } else {
            curr -> next = other_head; 
            other_head = other_head -> next;
        }
        curr = curr -> next;
    }
    
    curr -> next = head ? head : other_head;
    m_head = dummy.next;
    other.m_head = nullptr;
}

template <typename T>
void ForwardList<T>::merge(ForwardList&& other) {
    if (this == &other) {
        return;
    }

    Node dummy = {};
    Node* curr = &dummy; 
    Node* other_head = other.m_head;
    Node* head = m_head;
    
    while (head && other_head) {
        if (head -> val < other_head -> val) {
            curr -> next = head;
            head = head -> next;
        } else {
            curr -> next = other_head; 
            other_head = other_head -> next;
        }
        curr = curr -> next;
    }
    
    curr -> next = head ? head : other_head;
    m_head = dummy.next;
    other.m_head = nullptr;
}

template <typename T>
void ForwardList<T>::splice_after(ConstIterator pos, ForwardList& other) {
    Node* curr = const_cast<Node*>(pos.m_ptr);
    Node* rest = curr -> next;

    curr -> next = other.m_head;

    while (curr -> next) {
        curr = curr -> next;
    }

    curr -> next = rest;
    other.m_head = nullptr;
}

template <typename T>
void ForwardList<T>::splice_after(ConstIterator pos, ForwardList&& other) {
    Node* curr = const_cast<Node*>(pos.m_ptr);
    Node* rest = curr -> next;

    curr -> next = other.m_head;

    while (curr -> next) {
        curr = curr -> next;
    }

    curr -> next = rest;
    other.m_head = nullptr;
}

template <typename T>
void ForwardList<T>::splice_after(ConstIterator pos, ForwardList& other, ConstIterator it) {
    Node* curr = const_cast<Node*>(pos.m_ptr);
    Node* rest = curr -> next;
    Node* other_curr = const_cast<Node*>(it.m_ptr);

    curr -> next = other_curr -> next; 
    other_curr -> next = other_curr -> next -> next;
    curr -> next -> next = rest;
}

template <typename T>
void ForwardList<T>::splice_after(ConstIterator pos, ForwardList&& other, ConstIterator it) {
    Node* curr = const_cast<Node*>(pos.m_ptr);
    Node* rest = curr -> next;
    Node* other_curr = const_cast<Node*>(it.m_ptr);

    curr -> next = other_curr -> next; 
    other_curr -> next = other_curr -> next -> next;
    curr -> next -> next = rest;
}

template <typename T>
void ForwardList<T>::splice_after(ConstIterator pos, ForwardList& other, ConstIterator first, ConstIterator last) {
    Node* curr = const_cast<Node*>(pos.m_ptr);
    Node* rest = curr -> next;
    Node* first_o = const_cast<Node*>(first.m_ptr);
    Node* last_o = const_cast<Node*>(last.m_ptr);

    curr -> next = first_o -> next;
    first_o -> next = last_o;

    while (curr -> next != last_o) {
        curr = curr -> next;
    }
    curr -> next = rest;
}

template <typename T>
void ForwardList<T>::splice_after(ConstIterator pos, ForwardList&& other, ConstIterator first, ConstIterator last) {
    Node* curr = const_cast<Node*>(pos.m_ptr);
    Node* rest = curr -> next;
    Node* first_o = const_cast<Node*>(first.m_ptr);
    Node* last_o = const_cast<Node*>(last.m_ptr);

    curr -> next = first_o -> next;
    first_o -> next = last_o;

    while (curr -> next != last_o) {
        curr = curr -> next;
    }
    curr -> next = rest;
}

template <typename T>
template <typename Compare>
void ForwardList<T>::merge(ForwardList& other, Compare comp) {
    if (this == &other) {
        return;
    }

    Node dummy = {};
    Node* curr = &dummy; 
    Node* other_head = other.m_head;
    Node* head = m_head;
    
    while (head && other_head) {
        if (comp(head -> val, other_head -> val)) {
            curr -> next = head;
            head = head -> next;
        } else {
            curr -> next = other_head; 
            other_head = other_head -> next;
        }
        curr = curr -> next;
    }
    
    curr -> next = head ? head : other_head;
    m_head = dummy.next;
    other.m_head = nullptr;
}

template <typename T>
template <typename Compare>
void ForwardList<T>::merge(ForwardList&& other, Compare comp) {
    if (this == &other) {
        return;
    }

    Node dummy = {};
    Node* curr = &dummy; 
    Node* other_head = other.m_head;
    Node* head = m_head;
    
    while (head && other_head) {
        if (comp(head -> val, other_head -> val)) {
            curr -> next = head;
            head = head -> next;
        } else {
            curr -> next = other_head; 
            other_head = other_head -> next;
        }
        curr = curr -> next;
    }
    
    curr -> next = head ? head : other_head;
    m_head = dummy.next;
    other.m_head = nullptr;
}

template <typename T>
typename ForwardList<T>::size_type ForwardList<T>::remove(const_reference value) {
    Node dummy = {};
    dummy.next = m_head;

    Node* curr = m_head;
    Node* prev = &dummy;
    size_type count = 0;

    while (curr) {
        if (curr -> val == value) {
            prev -> next = curr -> next;
            delete curr;
            count++;
        } else {
            prev = curr;
        }
        curr = prev -> next;
    }

    m_head = dummy.next;
    return count;
}

template <typename T>
template <typename UnaryPredicate>
typename ForwardList<T>::size_type ForwardList<T>::remove_if(UnaryPredicate p) {
    Node dummy = {};
    dummy.next = m_head;

    Node* curr = m_head;
    Node* prev = &dummy;
    size_type count = 0;

    while (curr) {
        if (p(curr -> val)) {
            prev -> next = curr -> next;
            delete curr;
            count++;
        } else {
            prev = curr;
        }
        curr = prev -> next;
    }

    m_head = dummy.next;
    return count;
}

template <typename T>
void ForwardList<T>::reverce() noexcept {
    Node* curr = m_head;
    Node* prev = nullptr;
    Node* next = nullptr;

    while (curr) {
        next = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = next;
    }
    m_head = prev;
}

template <typename T>
typename ForwardList<T>::size_type ForwardList<T>::unique() noexcept {
    Node* curr = m_head;
    size_type count = 0;

    while (curr) {
        while (curr -> next && curr -> val == curr -> next -> val) {
            Node* tmp = curr -> next;
            curr -> next = curr -> next -> next;
            delete tmp;
            count++;
        }
        curr = curr -> next;
    }
    return count;
}

template <typename T>
void ForwardList<T>::sort() {
    sort_helper(m_head);
}

template <typename T>
typename ForwardList<T>::Node* ForwardList<T>::sort_helper(Node* head) {
    if (!head || !head -> next) {
        return head;
    }

    Node* second_half = split(head);

    return merge_helper(sort_helper(head), sort_helper(second_half));
}

template <typename T>
typename ForwardList<T>::Node* ForwardList<T>::split(Node* head) {
    Node* fast = head -> next;
    Node* slow = head;

    while (fast && fast -> next) {
        slow = slow -> next;
        fast = fast -> next -> next;
    }

    Node* second_half = slow -> next;
    slow -> next = nullptr;
    return second_half;
}

template <typename T>
typename ForwardList<T>::Node* ForwardList<T>::merge_helper(Node* L1, Node* L2) {
    if (!L1) {
        return L2;
    }

    if (!L2) {
        return L1;
    }

    if (L1 -> val <L2 -> val) {
        L1 -> next = merge_helper(L1 -> next, L2);
        return L1;
    } else {
        L2 -> next = merge_helper(L1, L2 -> next);
        return L2;
    }
}

template <typename T>
void ForwardList<T>::log() {
    Node* tmp = m_head;
    while (tmp) {
        std::cout << tmp -> val << " ";
        tmp = tmp -> next;
    }
    std::cout << std::endl;
}
