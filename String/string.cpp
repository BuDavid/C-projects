#include "string.hpp"

String::String() : m_ptr(nullptr), m_size(0), m_capacity(0) {}

String::String(const String& other) : m_ptr(nullptr), m_size(other.m_size), m_capacity(0) {
	allocate();
	strcpy(m_ptr, other.m_ptr);
}

String::String(const char* str) : m_ptr(nullptr), m_size(strlen(str)), m_capacity(0) {
	allocate();
	strcpy(m_ptr, str);
}

String::String(String&& other) noexcept {
    m_size = std::exchange(other.m_size, 0);
    m_capacity = std::exchange(other.m_capacity, 0);
    m_ptr = std::exchange(other.m_ptr, nullptr);
}

bool String::empty() const {
	return !m_size;
}

size_t String::capacity() const {
	return m_capacity;
}

size_t String::size() const {
	return m_size;
}

size_t String::length() const {
	return m_size;
}

void String::pop_back() {
	if (empty()) {
		return;
	}
	m_ptr[--m_size] = '\0';
}

void String::swap(String& str2) {
	int tmp = m_size;
	m_size = str2.m_size;
	str2.m_size = tmp;

	tmp = m_capacity;
	m_capacity = str2.m_capacity;
	str2.m_capacity = tmp;

	char* tmp_ptr = m_ptr;
	m_ptr = str2.m_ptr;
	str2.m_ptr = tmp_ptr;
}

String& String::operator=(const char* text) {
	clear();
	m_size = strlen(text);
	allocate();
	strcpy(m_ptr, text);
	return *this;
}

String& String::operator=(const String& other) {
    if (this != &other) {
        clear();
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        allocate();
        strcpy(m_ptr, other.m_ptr);
    }
	return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        clear();
        m_size = std::exchange(other.m_size, 0);
        m_capacity = std::exchange(other.m_capacity, 0);
        m_ptr = std::exchange(other.m_ptr, nullptr);
    }
	return *this;
}

bool String::operator==(const String& other) const {  
	if (strlen(other.m_ptr) != strlen(m_ptr)) {
		return false;
	}
	int idx = 0;
	while (other.m_ptr[idx] == m_ptr[idx]) {
		if (m_ptr[++idx] == '\0') {
			return true;
		}
	}
	return false;
}

String String::operator+(const String& other) {  
	char* tmp = new char[other.m_size + m_size];

	strcpy(tmp, m_ptr);
	strcat(tmp, other.m_ptr);
    String str_tmp(tmp);
    return str_tmp;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
	if (str.m_ptr) {
		os << str.m_ptr;
	}
	return os;
}

String& String::operator+=(const char* str) {  
	m_size += strlen(str);
	allocate();
	strcat(m_ptr, str);
    return *this;
}

String& String::operator+=(const String& other) {  
    if (this != &other) {
        m_size += other.m_size;
        allocate();
        strcat(m_ptr, other.m_ptr);
    }

    return *this;
}

char& String::operator[](int idx) {
	if (idx < 0 || idx >= m_size) {
		std::cerr << "Error" << std::endl;
	}
	return m_ptr[idx];
}

char& String::at(int idx) {
	if (idx < 0 || idx >= m_size) {
		std::cerr << "Error" << std::endl;
	}
	return m_ptr[idx];
}

char& String::front() {
	return m_ptr[0];
}

char& String::back() {
	return m_ptr[m_size-1];
}

void String::shrink_to_fit() {
	realloc();
}

void String::realloc() {
	if (!m_ptr) {
		return;
	}
	m_capacity = m_size;
	char* tmp = new char[m_capacity];
	strcpy(tmp, m_ptr);
	delete [] m_ptr;
	m_ptr = tmp;
}

void String::allocate() {
	if (m_capacity > m_size) {
		return;
	}

	while (m_capacity <= m_size) {
		m_capacity += 15;
	}
	if (!m_ptr) {
		m_ptr = new char[m_capacity];
		return;
	}
	char* tmp = new char[m_capacity];
	strcpy(tmp, m_ptr);
	delete [] m_ptr;
	m_ptr = tmp;
}

void String::clear() {
	if (m_ptr) {
		delete [] m_ptr;
	}

	m_size = 0;
	m_capacity = 0;
	m_ptr = nullptr;
}

int String::stoi() {
	int idx = 0;
	while (m_ptr[idx]) {
		if (m_ptr[idx] >= '0' && m_ptr[idx] <= '9') {
			break;
		}
		idx++;
	}
	if (!m_ptr[idx]) {
		return -1;
	}

	bool flag = false;
	if (idx != 0 && m_ptr[idx-1] == '-') {
		flag = true;
	}

	int ans = 0;
	while (m_ptr[idx] >= '0' && m_ptr[idx] <= '9') {
		ans *= 10;
		ans += m_ptr[idx++] - '0';
	}

	return flag ? -ans : ans;
}

void String::push_back(char ch) {
	m_ptr[m_size++] = ch;
	allocate();
	m_ptr[m_size] = '\0';
}

int String::compare(const String& str) const {
	if (*this == str) {
		return 0;
	}
	int idx = 0;
	while (m_ptr[idx] == str.m_ptr[idx]) {
		idx++;
		if (!m_ptr[idx]) {
			return -1;
		}
		if (!str.m_ptr[idx]) {
			return 1;
		}
	}
	return m_ptr[idx] > str.m_ptr[idx] ? 1 : -1;
}

int String::find(const char* str) const {
	char ch = str[0];
	int idx = 0;
	int ans = 0;
	const char* tmp = nullptr;
	while (m_ptr[idx]) {
		while (m_ptr[idx] != ch) {
			idx++;
			if (m_ptr[idx] == '\0') {
				return -1;
			}
		}

		tmp = str;
		ans = idx;
		while (*(++tmp) && m_ptr[++idx]) {
			if(*tmp != m_ptr[idx]) {
				break;
			}
		}

		if (*tmp == '\0') {
			return ans;
		}
	}
	return -1;
}

int String::find_first_of(char ch) const {
	if (!m_ptr) {
		return -1;
	}

	int idx = 0;
	while (m_ptr[idx]) {
		if (m_ptr[idx] == ch) {
			return idx;
		}
		idx++;
	}
	return -1;
}

void String::copy(String& str, int len) {
	if (len < 0) {
		return;
	}
	strcpy(m_ptr, str.m_ptr, len);
}

void String::erase(int start, int end) {
	if (start < 0 || end > m_size) {
		return;
	}
	if (start < end) {
		strcpy(m_ptr + start, m_ptr + end);
	} else if (!end && start < m_size) {
		strcpy(m_ptr + start, m_ptr + start + 1);
	}
}

void String::insert(const char* str, int start, int count) {
	if (start < 0 || count + start > m_size) {
		return;
	}
	int old_size = m_size;
	if (start < count) {
		m_size += count - start;
		allocate();
		strcpy(m_ptr + old_size, m_ptr + start, count - start);
		strcpy(m_ptr + start, str);
	} else if (!count && start < m_size) {
		m_size++;
		allocate();
		strcpy(m_ptr + old_size, m_ptr + start);
		m_ptr[start] = *str;
	}
}
		
void String::strcpy(char* dest, const char* source, int len) {
	if (!dest || !source) {
		return;
	}

	if (m_capacity < strlen(source)) {
		return;
	}

	int idx = 0;

	while (source[idx]) {
		if (len && idx >= len) {
			break;
		}
		dest[idx] = source[idx];
		idx++;
	}
	dest[idx] = '\0';
}
	
int String::strlen(const char* str) const {
	int len = 0;
	while (str[len]) {
	 	len++;
	}
	return len;
}

void String::strcat(char* dest, const char* source) {
	if (!dest || !source) {
		return;
	}

	while (*dest && dest++);
	strcpy(dest, source);
}

String::~String() {
	clear();
}

