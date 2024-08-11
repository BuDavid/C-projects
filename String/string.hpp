#ifndef STRING_H_  
#define STRING_H_  

#include <iostream>
#include <utility>

class String {
public:
	String();
	String(const char* str);
	String(const String& other);
	String(String&& other) noexcept;
	~String();
public:
	char& operator[](int idx);
	String operator+(const String& other);
	bool operator==(const String& other) const;
	String& operator=(const char* str);
	String& operator+=(const char* str);
	String& operator=(const String& other);
	String& operator+=(const String& other);
	String& operator=(String&& other) noexcept;
	friend std::ostream& operator<< (std::ostream& os, const String& str);
public:
	bool empty() const; 
	size_t size() const;
	size_t length() const;
	size_t capacity() const;
	char& back(); 
	char& front();
	char& at(const int idx);
	int stoi();
	int find(const char* str) const;
	int compare(const String& str) const;
	int find_first_of(const char ch) const;
	void clear(); 
	void pop_back();
	void shrink_to_fit();
	void swap(String& str2);
    void push_back(const char ch);
	void copy(String& str, int len = 0);
    void erase(const int start, const int end = 0);
	void insert(const char* str, const int start, const int end = 0);
private:
	int strlen(const char* str) const;
	void realloc();
	void allocate();
	void strcat(char* dest, const char* source);
	void strcpy(char* dest, const char* source, int len = 0);
private:
	char* m_ptr;
	size_t m_size;
	size_t m_capacity;
};

#endif   // STRING_H_  
