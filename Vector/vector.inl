#include "vector.hpp"

template <typename T>
Vector<T>::Vector() : m_ptr(nullptr), m_size(0), m_capacity(0) {}

template <typename T>
Vector<T>::Vector(const Vector& other) {
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	if (!other.m_ptr) {
		m_ptr = nullptr;
		return;
	}
	m_ptr = new int[m_capacity];
	for (int i = 0; i < m_size; i++) {
		m_ptr[i] = other.m_ptr[i];
	}
}

template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    m_size = std::exchange(other.m_size, 0);
    m_capacity = std::exchange(other.m_capacity, 0);
    m_ptr = std::exchange(other.m_ptr, nullptr);
}

template <typename T>
void Vector<T>::swap(Vector& other) {
	int tmp = m_size;
	m_size = other.m_size;
	other.m_size = tmp;

	tmp = m_capacity;
	m_capacity = other.m_capacity;
	other.m_capacity = tmp;

	int* tmp_ptr = m_ptr;
	m_ptr = other.m_ptr;
	other.m_ptr = tmp_ptr;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) { 
        clear();
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        m_ptr = new int[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_ptr[i] = other.m_ptr[i];
        }
    }

    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        m_size = std::exchange(other.m_size, 0);
        m_capacity = std::exchange(other.m_capacity, 0);
        m_ptr = std::exchange(other.m_ptr, nullptr);
    }
    return *this;
}

template <typename T>
void Vector<T>::insert(int idx, T element) {
	if (idx < 0 || idx > m_size) {
		return;
	}
	if (m_size + 1 >= m_capacity) {
		allocate();
	}
	for (int i = m_size; i > idx; i--) {
		m_ptr[i] = m_ptr[i-1];
	}
	m_size++;
	m_ptr[idx] = element;
}

template <typename T>
void Vector<T>::erase(int idx) {
	if (idx < 0 || idx >= m_size) {
		return;
	}
	m_size--;
	while (idx < m_size) {
		m_ptr[idx] = m_ptr[idx+1];
		idx++;
	}
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& other) {
	if (other.m_ptr) {
		for (int i = 0; i < other.m_size; i++) {
			os << other.m_ptr[i] << ' ';
		}
		os << std::endl;
	}
	return os;
}

template <typename T>
bool Vector<T>::operator==(const Vector& other) const {
	if (m_size != other.m_size) {
		return 0;
	}
	for (int i = 0; i < m_size; i++) {
		if (m_ptr[i] != other.m_ptr[i]) {
			return 0;
		}
	}
	return 1;
}

template <typename T>
T& Vector<T>::operator[](int idx) {
	return m_ptr[idx];
}

template <typename T>
T& Vector<T>::at(int idx) {
	if (idx < 0 || idx >= m_size) {
		std::cout << "Out of range" << std::endl;
		std::exit(1);
	}
	return m_ptr[idx];
}

template <typename T>
T& Vector<T>::front() {
	return m_ptr[0];
}

template <typename T>
T& Vector<T>::back() {
	return m_ptr[m_size-1];
}

template <typename T>
void Vector<T>::push_back(T element) {
	if (m_size + 1 >= m_capacity) {
		allocate();
	}
	m_ptr[m_size++] = element;
}

template <typename T>
void Vector<T>::pop_back() {
	if (m_size) {
		m_size--;
	}
}

template <typename T>
bool Vector<T>::empty() const {
	return !m_size;
}

template <typename T>
size_t Vector<T>::size() const {
	return m_size;
}

template <typename T>
size_t Vector<T>::capacity() const {
	return m_capacity;
}

template <typename T>
void Vector<T>::clear() {
	m_size = 0;
	m_capacity = 0;
	if (m_ptr) {
		delete [] m_ptr;
	}
	m_ptr = nullptr;
}

template <typename T>
void Vector<T>::shrink_to_fit() {
	if (m_size == m_capacity) {
		return;
	}
	m_capacity = m_size; 
	resize();
}

template <typename T>
void Vector<T>::allocate() {
	if (!m_ptr) {
		m_capacity++;
		m_ptr = new int[m_capacity];
		return;
	}
	if (m_size >= m_capacity) {
		m_capacity *= 2;
	}
	resize();	
}

template <typename T>
void Vector<T>::resize() {
	int* tmp = m_ptr;
	m_ptr = new int[m_capacity];
	for (int i = 0; i < m_size; i++) {
		m_ptr[i] = tmp[i];
	}
	delete [] tmp;
	tmp = nullptr;
}

template <typename T>
Vector<T>::~Vector() {
	clear();
}
