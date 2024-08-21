#ifndef VECTOR_H_
#define VECTOR_H_

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>
#include <stdexcept>

template <typename T>
class Vector;

template <typename T>
std::ostream& operator<< (std::ostream& os, const Vector<T>& other); 

template <typename T>
class Vector {
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    class Iterator;
    class ConstIterator;
    class ReverseIterator;
    class CReverseIterator;
public:
	Vector() noexcept;
	explicit Vector(size_type count, const_reference value = T());
	Vector(const std::initializer_list<T>& list);
	Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
	~Vector();
public:
	reference operator[](size_type idx) noexcept;
	const_reference operator[](size_type idx) const noexcept;
	Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
	bool operator==(const Vector& other) const;
	friend std::ostream& operator<< <T> (std::ostream& os, const Vector<T>& other); 
public:
    bool empty() const;
    size_type size() const; 
    size_type max_size() const; 
    size_type capacity() const;
    pointer data();
    const_pointer data() const;
    reference back();
    const_reference back() const;
    reference front();
    const_reference front() const;
    reference at(size_type idx);
    const_reference at(size_type idx) const;
    void clear();
    void pop_back();
    void shrink_to_fit();
    void reserve(size_type new_cap);
    void push_back(const_reference element);
    void push_back(value_type&& element);
    void resize(size_type count);
    void resize(size_type count, const_reference value);
    void swap(Vector& other) noexcept;
    ConstIterator begin() const;
    Iterator begin();
    ConstIterator end() const;
    Iterator end();
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    CReverseIterator rbegin() const;
    ReverseIterator rbegin();
    CReverseIterator rend() const;
    ReverseIterator rend();
    CReverseIterator crbegin() const noexcept;
    CReverseIterator crend() const noexcept;
    Iterator erase(const Iterator& pos);
    Iterator erase(const Iterator& first, const Iterator& last);
    Iterator insert(const Iterator& pos, const_reference value);
    Iterator insert(const Iterator& pos, value_type&& value);
    Iterator insert(const Iterator& pos, Iterator first, Iterator last);
private:
	pointer m_ptr;
	size_type m_size;
	size_type m_capacity;
};

#include "vector_iterator.hpp"
#include "vector_const_iterator.hpp"
#include "vector_reverse_iterator.hpp"
#include "vector_const_reverse_iterator.hpp"
#include "vector.inl"

#endif  // VECTOR_H_

