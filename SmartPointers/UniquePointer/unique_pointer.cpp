#include "unique_pointer.hpp"

template <typename T>
unique_pointer<T>::unique_pointer(T* ptr) : m_ptr(ptr) {}

template <typename T>
unique_pointer<T>::unique_pointer(unique_pointer&& other) {
    m_ptr = other.release();
}

template <typename T>
unique_pointer<T>::~unique_pointer() {
    reset();
}

template <typename T>
T* unique_pointer<T>::release() {
    T* tmp = m_ptr;
    m_ptr = nullptr;
    return tmp;
}

template <typename T>
void unique_pointer<T>::reset(T* ptr) noexcept {
    if (m_ptr) {
        delete m_ptr;
    }
    m_ptr = ptr;
}

template <typename T>
unique_pointer<T>& unique_pointer<T>::operator=(unique_pointer&& other) {
    if (this != &other) {
        reset(other.release());
    }
    return *this;
}

template <typename T>
T* unique_pointer<T>::operator->() {
    return m_ptr;
}

template <typename T>
T& unique_pointer<T>::operator*() {
    return *m_ptr;
}

template <typename T>
unique_pointer<T>::operator bool() const {
    return m_ptr != nullptr;
}

