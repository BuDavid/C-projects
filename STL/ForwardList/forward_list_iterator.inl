#include "forward_list_iterator.hpp"

template <typename T>
ForwardList<T>::Iterator::Iterator(Node* ptr) : m_ptr(ptr) {}

template <typename T>
typename ForwardList<T>::Iterator::reference ForwardList<T>::Iterator::operator*() const {
    return m_ptr -> val;
}

template <typename T>
typename ForwardList<T>::Iterator::pointer ForwardList<T>::Iterator::operator->() const {
    return &(m_ptr -> val);
}

template <typename T>
typename ForwardList<T>::Iterator& ForwardList<T>::Iterator::operator++() {
    m_ptr = m_ptr -> next;
    return *this;
}

template <typename T>
typename ForwardList<T>::Iterator ForwardList<T>::Iterator::operator++(int) {
    Iterator tmp(*this);
    m_ptr = m_ptr -> next;
    return tmp;
}

template <typename T>
bool ForwardList<T>::Iterator::operator==(const Iterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool ForwardList<T>::Iterator::operator!=(const Iterator& other) const {
    return m_ptr != other.m_ptr;
}
