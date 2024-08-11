#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream>
#include <utility>

template <typename T>
class Vector;

template <typename T>
std::ostream& operator<< (std::ostream& os, const Vector<T>& other); 

template <typename T>
class Vector {
public:
	Vector();
	Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
	~Vector();
public:
	T& operator[](int idx);
	Vector& operator=(const Vector& other);
	bool operator==(const Vector& other) const;
    Vector<T>& operator=(Vector&& other) noexcept;
	friend std::ostream& operator<< <T> (std::ostream& os, const Vector<T>& other); 
public:
    bool empty() const;
    size_t size() const; 
    size_t capacity() const;
    T& back();
    T& front();
    T& at(int idx);
    void clear();
    void pop_back();
    void shrink_to_fit();
    void erase(int idx);
    void swap(Vector& other);
    void push_back(T element);
    void insert(int idx, T element);
private:
	void resize();
	void allocate();
private:
	T* m_ptr;
	size_t m_size;
	size_t m_capacity;
};

#include "vector.inl"

#endif  // VECTOR_H_

