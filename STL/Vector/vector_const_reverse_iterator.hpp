#ifndef VECTOR_CONST_REVERSE_ITERATOR_H_
#define VECTOR_CONST_REVERSE_ITERATOR_H_

#include "vector.hpp"
#include <iterator>
#include <cstddef>

template <typename T>
class Vector<T>::CReverseIterator {
public:
    using value_type = T;
    using reference = const T&;
    using pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
public:
    CReverseIterator(pointer ptr = nullptr);
public:
    reference operator*() const;
    reference operator->() const;
    CReverseIterator& operator++();
    CReverseIterator operator++(int);
    CReverseIterator& operator--();
    CReverseIterator operator--(int);
    CReverseIterator& operator+=(difference_type rai);
    CReverseIterator& operator-=(difference_type rai);
    CReverseIterator operator+(difference_type rai) const;
    CReverseIterator operator-(difference_type rai) const;
    difference_type operator-(const CReverseIterator& other) const;
    reference operator[](difference_type rai) const;
    bool operator==(const CReverseIterator& other) const;
    bool operator!=(const CReverseIterator& other) const;
    bool operator<(const CReverseIterator& other) const; 
    bool operator<=(const CReverseIterator& other) const;
    bool operator>(const CReverseIterator& other) const; 
    bool operator>=(const CReverseIterator& other) const;
private:
    pointer m_ptr;
};

#include "vector_const_reverse_iterator.inl"

#endif  // VECTOR_CONST_REVERSE_ITERATOR_H_
