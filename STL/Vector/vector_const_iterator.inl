#include "vector_const_iterator.hpp"

template <typename T>
Vector<T>::ConstIterator::ConstIterator(pointer ptr) : m_ptr(ptr) {}

template <typename T>
typename Vector<T>::ConstIterator::reference Vector<T>::ConstIterator::operator*() const {
    return *m_ptr;
}

template <typename T>
typename Vector<T>::ConstIterator::reference Vector<T>::ConstIterator::operator->() const {
    return *m_ptr;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++() {
    m_ptr++;
    return *this;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int) {
    ConstIterator tmp(m_ptr);
    m_ptr++;
    return tmp;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator--() {
    m_ptr--;
    return *this;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator--(int) {
    ConstIterator tmp(m_ptr);
    m_ptr--;
    return tmp;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator+=(difference_type rai) {
    m_ptr += rai;
    return *this;
}

template <typename T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator-=(difference_type rai) {
    m_ptr -= rai;
    return *this;
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator+(difference_type rai) const {
    return ConstIterator(m_ptr + rai);
}

template <typename T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator-(difference_type rai) const {
    return ConstIterator(m_ptr - rai);
}

template <typename T>
typename Vector<T>::ConstIterator::difference_type Vector<T>::ConstIterator::operator-(const ConstIterator& other) const {
    return m_ptr - other.m_ptr;
}

template <typename T>
typename Vector<T>::ConstIterator::reference Vector<T>::ConstIterator::operator[](difference_type rai) const {
    return *(m_ptr + rai);
}

template <typename T>
bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const {
    return m_ptr == other.m_ptr;
}

template <typename T>
bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const {
    return m_ptr != other.m_ptr;
}

template <typename T>
bool Vector<T>::ConstIterator::operator<=(const ConstIterator& other) const {
    return m_ptr <= other.m_ptr;
}
template <typename T>
bool Vector<T>::ConstIterator::operator>=(const ConstIterator& other) const {
    return m_ptr >= other.m_ptr;
}
template <typename T>
bool Vector<T>::ConstIterator::operator<(const ConstIterator& other) const {
    return m_ptr < other.m_ptr;
}
template <typename T>
bool Vector<T>::ConstIterator::operator>(const ConstIterator& other) const {
    return m_ptr > other.m_ptr;
}
