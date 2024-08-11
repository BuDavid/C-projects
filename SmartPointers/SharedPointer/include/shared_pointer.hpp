#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include <utility>
#include "control_block.hpp"

template <typename T>
class weak_pointer;

template <typename T>
class shared_pointer {
public:
    shared_pointer(T* ptr = nullptr);
    shared_pointer(const shared_pointer& other);
    shared_pointer(shared_pointer&& other);
    shared_pointer(const weak_pointer<T>& other);
    ~shared_pointer();
public:
    shared_pointer& operator=(shared_pointer& other);    
    shared_pointer& operator=(shared_pointer&& other);    
    T& operator*();    
    T* operator->();    
public:
    void reset(T* ptr) noexcept;
private:
    void deleter();
private:
    T* m_ptr;
    control_block* m_cb;
    friend class weak_pointer<T>;
};

#include "shared_pointer.inl"

#endif  // SHARED_POINTER_H
