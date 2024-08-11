#include "shared_pointer.hpp"

template <typename T>
shared_pointer<T>::shared_pointer(T* ptr) : m_ptr(ptr), m_cb(new control_block) {
    m_cb -> m_smart_count++;
}

template <typename T>
shared_pointer<T>::shared_pointer(const shared_pointer<T>& other) : m_ptr(other.m_ptr), m_cb(other.m_cb) {
    m_cb -> m_smart_count++;
}

template <typename T>
shared_pointer<T>::shared_pointer(shared_pointer<T>&& other) : m_ptr(std::exchange(other.m_ptr, nullptr)), m_cb(std::exchange(other.m_cb, nullptr)) {}

template <typename T>
shared_pointer<T>& shared_pointer<T>::operator=(shared_pointer<T>&& other) {
    deleter();
    m_ptr = std::exchange(other.m_ptr, nullptr);
    m_cb = std::exchange(other.m_cb, nullptr);
    return *this;
}

template <typename T>
shared_pointer<T>::shared_pointer(const weak_pointer<T>& other) : m_ptr(other.m_ptr), m_cb(other.m_cb) {
    m_cb -> m_smart_count++;
}

template <typename T>
shared_pointer<T>& shared_pointer<T>::operator=(shared_pointer& other) { 
    deleter();
    m_ptr = other -> m_ptr; 
    m_cb = other -> m_cb;
    m_cb -> m_smart_count++;
    return *this;
}

template <typename T>
T& shared_pointer<T>::operator*() { 
    return *m_ptr;
}

template <typename T>
T* shared_pointer<T>::operator->() { 
    return m_ptr;
}

template <typename T>
void shared_pointer<T>::reset(T* ptr) noexcept {
    deleter();
    m_ptr = ptr; 
    m_cb = new control_block;
    m_cb -> m_smart_count++;
}

template <typename T>
void shared_pointer<T>::deleter() {
    int count = --(m_cb -> m_smart_count);
    if (count == 0) {
        delete m_ptr;
        m_ptr = nullptr;

        if (m_cb -> m_weak_count == 0) {
            delete m_cb;
            m_cb = nullptr;
        }
    }
}

template <typename T>
shared_pointer<T>::~shared_pointer() {
    deleter();
}

