#ifndef VECTOR_ITERATOR_H_
#define VECTOR_ITERATOR_H_

#include "vector.hpp"
#include <iterator>
#include <cstddef>

template <typename T>
class Vector<T>::Iterator {
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
public:
    Iterator(pointer ptr = nullptr);
public:
    reference operator*() const;
    reference operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    Iterator& operator--();
    Iterator operator--(int);
    Iterator& operator+=(difference_type rai);
    Iterator& operator-=(difference_type rai);
    Iterator operator+(difference_type rai) const;
    Iterator operator-(difference_type rai) const;
    difference_type operator-(const Iterator& other) const;
    reference operator[](difference_type rai);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    bool operator<(const Iterator& other) const; 
    bool operator<=(const Iterator& other) const;
    bool operator>(const Iterator& other) const; 
    bool operator>=(const Iterator& other) const;
private:
    pointer m_ptr;
};

#include "vector_iterator.inl"

#endif  // VECTOR_ITERATOR_H_
