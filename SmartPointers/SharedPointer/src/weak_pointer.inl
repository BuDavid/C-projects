#include "weak_pointer.hpp"

template <typename T>
weak_pointer<T>::weak_pointer(const shared_pointer<T>& other) : m_ptr(other.m_ptr), m_cb(other.m_cb) {
    m_cb -> m_weak_count++;
}

template <typename T>
weak_pointer<T>::weak_pointer(const weak_pointer& other) : m_ptr(other.m_ptr), m_cb(other.m_cb) {
    m_cb -> m_weak_count++;
}

template <typename T>
weak_pointer<T>::weak_pointer(weak_pointer&& other) {
    m_ptr = std::exchange(other.m_ptr, nullptr);
    m_cb = std::exchange(other.m_cb, nullptr);
}

template <typename T>
weak_pointer<T>& weak_pointer<T>::operator=(weak_pointer& other) {
    deleter();
    m_ptr = other.m_ptr;
    m_cb = other.m_cb;
    m_cb -> m_weak_count++;
    return *this;
}

template <typename T>
weak_pointer<T>& weak_pointer<T>::operator=(weak_pointer&& other) {
    deleter();
    m_ptr = std::exchange(other.m_ptr, nullptr);
    m_cb = std::exchange(other.m_cb, nullptr);
    return *this;
}

template <typename T>
void weak_pointer<T>::deleter() {
    int count = --(m_cb -> m_weak_count);
    if (count == 0 && m_cb -> m_smart_count == 0) {
        delete m_cb;
    }
}

template <typename T>
shared_pointer<T> weak_pointer<T>::lock() {
    if (m_cb -> m_smart_count) {
        return shared_pointer(*this);
    }
    return nullptr;
}

template <typename T>
weak_pointer<T>::~weak_pointer() {
    deleter();
}
