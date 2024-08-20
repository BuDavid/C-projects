#include "vector_reverse_iterator.hpp"

template <typename T>
Vector<T>::ReverseIterator::ReverseIterator(pointer ptr) : m_ptr(ptr) {}

template <typename T>
typename Vector<T>::ReverseIterator::reference Vector<T>::ReverseIterator::operator*() const {
    return *(m_ptr - 1);
}

template <typename T>
typename Vector<T>::ReverseIterator::reference Vector<T>::ReverseIterator::operator->() const {
    return *(m_ptr - 1);
}

template <typename T>
typename Vector<T>::ReverseIterator& Vector<T>::ReverseIterator::operator++() {
    m_ptr--;
    return *this;
}

template <typename T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator++(int) {
    ReverseIterator tmp(m_ptr);
    m_ptr--;
    return tmp;
}

template <typename T>
typename Vector<T>::ReverseIterator& Vector<T>::ReverseIterator::operator--() {
    m_ptr++;
    return *this;
}

template <typename T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator--(int) {
    ReverseIterator tmp(m_ptr);
    m_ptr++;
    return tmp;
}

template <typename T>
typename Vector<T>::ReverseIterator& Vector<T>::ReverseIterator::operator+=(difference_type rai) {
    m_ptr -= rai;
    return *this;
}

template <typename T>
typename Vector<T>::ReverseIterator& Vector<T>::ReverseIterator::operator-=(difference_type rai) {
    m_ptr += rai;
    return *this;
}

template <typename T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator+(difference_type rai) const {
    return ReverseIterator(m_ptr - rai);
}

template <typename T>
typename Vector<T>::ReverseIterator Vector<T>::ReverseIterator::operator-(difference_type rai) const {
    return ReverseIterator(m_ptr + rai);
}

template <typename T>
typename Vector<T>::difference_type Vector<T>::ReverseIterator::operator-(const ReverseIterator& other) const {
    return other.m_ptr - m_ptr;
}

template <typename T>
typename Vector<T>::reference Vector<T>::ReverseIterator::operator[](difference_type rai) {
    return *(m_ptr - rai);
}

template <typename T>
bool Vector<T>::ReverseIterator::operator==(const ReverseIterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool Vector<T>::ReverseIterator::operator!=(const ReverseIterator& other) const {
    return m_ptr != other.m_ptr;
}

template <typename T>
bool Vector<T>::ReverseIterator::operator<=(const ReverseIterator& other) const {
    return m_ptr >= other.m_ptr;
}
template <typename T>
bool Vector<T>::ReverseIterator::operator>=(const ReverseIterator& other) const {
    return m_ptr <= other.m_ptr;
}
template <typename T>
bool Vector<T>::ReverseIterator::operator<(const ReverseIterator& other) const {
    return m_ptr > other.m_ptr;
}
template <typename T>
bool Vector<T>::ReverseIterator::operator>(const ReverseIterator& other) const {
    return m_ptr < other.m_ptr;
}
