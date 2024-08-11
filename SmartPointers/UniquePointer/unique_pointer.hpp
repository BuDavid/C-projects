#ifndef UNIQUE_POINTER_H_
#define UNIQUE_POINTER_H_

template <typename T>
class unique_pointer final {
public:
    unique_pointer(T* ptr = nullptr);
    unique_pointer(unique_pointer&& other);
    ~unique_pointer();
public:
    T* release();
    void reset(T* ptr = nullptr) noexcept;
    unique_pointer& operator=(unique_pointer&& other);
    T* operator->();
    T& operator*();
    explicit operator bool() const;
private:
    unique_pointer(const unique_pointer& ptr) = delete;
    unique_pointer& operator=(const unique_pointer& ptr) = delete;
private:
    T* m_ptr;
};

#endif  // UNIQUE_POINTER_H_
