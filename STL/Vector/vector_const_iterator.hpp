#ifndef VECTOR_CONST_ITERATOR_H_
#define VECTOR_CONST_ITERATOR_H_

#include "vector.hpp"
#include <iterator>
#include <cstddef>

template <typename T>
class Vector<T>::ConstIterator {
public:
    using value_type = T;
    using reference = const T&;
    using pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::random_access_iterator_tag;
public:
    ConstIterator(pointer ptr = nullptr);
public:
    reference operator*() const;
    reference operator->() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    ConstIterator& operator--();
    ConstIterator operator--(int);
    ConstIterator& operator+=(difference_type rai);
    ConstIterator& operator-=(difference_type rai);
    ConstIterator operator+(difference_type rai) const;
    ConstIterator operator-(difference_type rai) const;
    difference_type operator-(const ConstIterator& other) const;
    reference operator[](difference_type rai) const;
    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;
    bool operator<(const ConstIterator& other) const; 
    bool operator<=(const ConstIterator& other) const;
    bool operator>(const ConstIterator& other) const; 
    bool operator>=(const ConstIterator& other) const;
private:
    pointer m_ptr;
};

#include "vector_const_iterator.inl"

#endif  // VECTOR_CONST_ITERATOR_H_
