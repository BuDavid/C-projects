#ifndef VECTOR_REVERSE_ITERATOR_H_
#define VECTOR_REVERSE_ITERATOR_H_

#include "vector.hpp"
#include <iterator>
#include <cstddef>

template <typename T>
class Vector<T>::ReverseIterator {
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
public:
    ReverseIterator(pointer ptr = nullptr);
public:
    reference operator*() const;
    reference operator->() const;
    ReverseIterator& operator++();
    ReverseIterator operator++(int);
    ReverseIterator& operator--();
    ReverseIterator operator--(int);
    ReverseIterator& operator+=(difference_type rai);
    ReverseIterator& operator-=(difference_type rai);
    ReverseIterator operator+(difference_type rai) const;
    ReverseIterator operator-(difference_type rai) const;
    difference_type operator-(const ReverseIterator& other) const;
    reference operator[](difference_type rai);
    bool operator==(const ReverseIterator& other) const;
    bool operator!=(const ReverseIterator& other) const;
    bool operator<(const ReverseIterator& other) const; 
    bool operator<=(const ReverseIterator& other) const;
    bool operator>(const ReverseIterator& other) const; 
    bool operator>=(const ReverseIterator& other) const;
private:
    pointer m_ptr;
};

#include "vector_reverse_iterator.inl"

#endif  // VECTOR_REVERSE_ITERATOR_H_
