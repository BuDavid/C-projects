#ifndef FORWARD_LSIT_H_
#define FORWARD_LSIT_H_

#include <iostream>
#include <initializer_list>
#include <utility>
#include <limits>
#include <cstddef>

template <typename T>
class ForwardList {
public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    class Iterator;
    class ConstIterator;
private:
    struct Node {
        Node(const_reference value = value_type()) : val(value), next(nullptr) {}
        Node(value_type&& value) : val(move(value)), next(nullptr) {}
        value_type val;
        Node* next;
     };
public:
    ForwardList();
    explicit ForwardList(const size_type size);
    explicit ForwardList(const size_type size, const_reference value);
    ForwardList(const std::initializer_list<T>& list);
    ForwardList(const ForwardList& other);
    ForwardList(ForwardList&& other);
    ~ForwardList();
public:
    ForwardList& operator=(const ForwardList& other);
    ForwardList& operator=(ForwardList&& other) noexcept;
    ForwardList& operator=(const std::initializer_list<T>& list);
    bool operator==(const ForwardList& other) const;
    bool operator!=(const ForwardList& other) const;
    bool operator>(const ForwardList& other) const;
    bool operator<(const ForwardList& other) const;
    bool operator>=(const ForwardList& other) const;
    bool operator<=(const ForwardList& other) const;
public:
    reference front();
    const_reference front() const;
    bool empty() const noexcept;
    size_type max_size() const noexcept;
    void clear() noexcept;
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ConstIterator cbegin() const noexcept;
    ConstIterator cend() const noexcept;
    Iterator insert_after(ConstIterator pos, const_reference value);
    Iterator insert_after(ConstIterator pos, value_type&& value);
    Iterator insert_after(ConstIterator pos, size_type count, const_reference value);
    Iterator insert_after(ConstIterator pos, const std::initializer_list<T>& list);
    Iterator erase_after(ConstIterator pos);
    Iterator erase_after(ConstIterator first, ConstIterator last);
    void push_front(const_reference value);
    void push_front(value_type&& value);
    void pop_front();
    void resize(size_type count, const_reference value = 0);
    void swap(ForwardList& other) noexcept;
    void merge(ForwardList& other);
    void merge(ForwardList&& other);
    void splice_after(ConstIterator pos, ForwardList& other);
    void splice_after(ConstIterator pos, ForwardList&& other);
    void splice_after(ConstIterator pos, ForwardList& other, ConstIterator it);
    void splice_after(ConstIterator pos, ForwardList&& other, ConstIterator it);
    void splice_after(ConstIterator pos, ForwardList& other, ConstIterator first, ConstIterator last);
    void splice_after(ConstIterator pos, ForwardList&& other, ConstIterator first, ConstIterator last);
    size_type remove(const_reference value);
    void reverce() noexcept;
    size_type unique() noexcept;
    void sort();
    void log();
public:
    template <typename InputIt>
    Iterator insert_after(ConstIterator pos, InputIt first, InputIt last);

    template <typename UnaryPredicate>
    size_type remove_if(UnaryPredicate p);

    template <typename Compare>
    void merge(ForwardList& other, Compare comp);

    template <typename Compare>
    void merge(ForwardList&& other, Compare comp);
private:
    Node* sort_helper(Node* head);
    Node* split(Node* head);
    Node* merge_helper(Node* l1, Node* l2);
private:
    Node* m_head;
};

#include "forward_list_iterator.hpp"
#include "forward_list_const_iterator.hpp"
#include "forward_list.inl"

#endif  // FORWARD_LSIT_H_
