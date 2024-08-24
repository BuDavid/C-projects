#include "vector_const_reverse_iterator.hpp"

template <typename T>
Vector<T>::CReverseIterator::CReverseIterator(pointer ptr) : m_ptr(ptr) {}

template <typename T>
typename Vector<T>::CReverseIterator::reference Vector<T>::CReverseIterator::operator*() const {
    return *(m_ptr - 1);
}

template <typename T>
typename Vector<T>::CReverseIterator::reference Vector<T>::CReverseIterator::operator->() const {
    return *(m_ptr - 1);
}

template <typename T>
typename Vector<T>::CReverseIterator& Vector<T>::CReverseIterator::operator++() {
    m_ptr--;
    return *this;
}

template <typename T>
typename Vector<T>::CReverseIterator Vector<T>::CReverseIterator::operator++(int) {
    CReverseIterator tmp(m_ptr);
    m_ptr--;
    return tmp;
}

template <typename T>
typename Vector<T>::CReverseIterator& Vector<T>::CReverseIterator::operator--() {
    m_ptr++;
    return *this;
}

template <typename T>
typename Vector<T>::CReverseIterator Vector<T>::CReverseIterator::operator--(int) {
    CReverseIterator tmp(m_ptr);
    m_ptr++;
    return tmp;
}

template <typename T>
typename Vector<T>::CReverseIterator& Vector<T>::CReverseIterator::operator+=(difference_type rai) {
    m_ptr -= rai;
    return *this;
}

template <typename T>
typename Vector<T>::CReverseIterator& Vector<T>::CReverseIterator::operator-=(difference_type rai) {
    m_ptr += rai;
    return *this;
}

template <typename T>
typename Vector<T>::CReverseIterator Vector<T>::CReverseIterator::operator+(difference_type rai) const {
    return CReverseIterator(m_ptr - rai);
}

template <typename T>
typename Vector<T>::CReverseIterator Vector<T>::CReverseIterator::operator-(difference_type rai) const {
    return CReverseIterator(m_ptr + rai);
}

template <typename T>
typename Vector<T>::CReverseIterator::difference_type Vector<T>::CReverseIterator::operator-(const CReverseIterator& other) const {
    return other.m_ptr - m_ptr;
}

template <typename T>
typename Vector<T>::CReverseIterator::reference Vector<T>::CReverseIterator::operator[](difference_type rai) const {
    return *(m_ptr - rai);
}

template <typename T>
bool Vector<T>::CReverseIterator::operator==(const CReverseIterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool Vector<T>::CReverseIterator::operator!=(const CReverseIterator& other) const {
    return m_ptr != other.m_ptr;
}

template <typename T>
bool Vector<T>::CReverseIterator::operator<=(const CReverseIterator& other) const {
    return m_ptr >= other.m_ptr;
}
template <typename T>
bool Vector<T>::CReverseIterator::operator>=(const CReverseIterator& other) const {
    return m_ptr <= other.m_ptr;
}
template <typename T>
bool Vector<T>::CReverseIterator::operator<(const CReverseIterator& other) const {
    return m_ptr > other.m_ptr;
}
template <typename T>
bool Vector<T>::CReverseIterator::operator>(const CReverseIterator& other) const {
    return m_ptr < other.m_ptr;
}
