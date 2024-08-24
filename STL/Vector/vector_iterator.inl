#include "vector_iterator.hpp"

template <typename T>
Vector<T>::Iterator::Iterator(pointer ptr) : m_ptr(ptr) {}

template <typename T>
typename Vector<T>::Iterator::reference Vector<T>::Iterator::operator*() const {
    return *m_ptr;
}

template <typename T>
typename Vector<T>::Iterator::reference Vector<T>::Iterator::operator->() const {
    return *m_ptr;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
    m_ptr++;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
    Iterator tmp(m_ptr);
    m_ptr++;
    return tmp;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--() {
    m_ptr--;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int) {
    Iterator tmp(m_ptr);
    m_ptr--;
    return tmp;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator+=(difference_type rai) {
    m_ptr += rai;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator-=(difference_type rai) {
    m_ptr -= rai;
    return *this;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(difference_type rai) const {
    return Iterator(m_ptr + rai);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(difference_type rai) const {
    return Iterator(m_ptr - rai);
}

template <typename T>
typename Vector<T>::difference_type Vector<T>::Iterator::operator-(const Iterator& other) const {
    return m_ptr - other.m_ptr;
}

template <typename T>
typename Vector<T>::reference Vector<T>::Iterator::operator[](difference_type rai) {
    return *(m_ptr + rai);
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& other) const {
    return m_ptr != other.m_ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator<=(const Iterator& other) const {
    return m_ptr <= other.m_ptr;
}
template <typename T>
bool Vector<T>::Iterator::operator>=(const Iterator& other) const {
    return m_ptr >= other.m_ptr;
}
template <typename T>
bool Vector<T>::Iterator::operator<(const Iterator& other) const {
    return m_ptr < other.m_ptr;
}
template <typename T>
bool Vector<T>::Iterator::operator>(const Iterator& other) const {
    return m_ptr > other.m_ptr;
}
