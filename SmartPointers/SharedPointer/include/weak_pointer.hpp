#ifndef WEAK_POINTER_H_
#define WEAK_POINTER_H_

#include <utility>
#include "control_block.hpp"

template <typename T>
class shared_pointer;

template <typename T>
class weak_pointer {
public:
    weak_pointer(const shared_pointer<T>& other);
    weak_pointer(const weak_pointer& other);
    weak_pointer(weak_pointer&& other);
    ~weak_pointer();
public:
    weak_pointer& operator=(weak_pointer& other);    
    weak_pointer& operator=(weak_pointer&& other);    
public:
    shared_pointer<T> lock();
    void reset(T* ptr) noexcept;
private:
    void deleter();
private:
    T* m_ptr;
    control_block* m_cb;
    friend class shared_pointer<T>;
};

#include "weak_pointer.inl"

#endif  // WEAK_POINTER_H_
