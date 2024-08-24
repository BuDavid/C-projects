#include "forward_list_const_iterator.hpp"

template <typename T>
ForwardList<T>::ConstIterator::ConstIterator(const Node* ptr) : m_ptr(ptr) {}

template <typename T>
ForwardList<T>::ConstIterator::ConstIterator(const Iterator& ptr) : m_ptr(ptr.m_ptr) {}

template <typename T>
typename ForwardList<T>::ConstIterator::reference ForwardList<T>::ConstIterator::operator*() const {
    return m_ptr -> val;
}

template <typename T>
typename ForwardList<T>::ConstIterator::pointer ForwardList<T>::ConstIterator::operator->() const {
    return &(m_ptr -> val);
}

template <typename T>
typename ForwardList<T>::ConstIterator& ForwardList<T>::ConstIterator::operator++() {
    m_ptr = m_ptr -> next;
    return *this;
}

template <typename T>
typename ForwardList<T>::ConstIterator ForwardList<T>::ConstIterator::operator++(int) {
    ConstIterator tmp(*this);
    m_ptr = m_ptr -> next;
    return tmp;
}

template <typename T>
bool ForwardList<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool ForwardList<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return m_ptr != other.m_ptr;
}
