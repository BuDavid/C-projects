#ifndef FORWARD_LIST_CONST_ITERATOR_H_
#define FORWARD_LIST_CONST_ITERATOR_H_

#include "forward_list.hpp"
#include <iterator>

template <typename T>
class ForwardList<T>::ConstIterator {
public:
    using value_type = T;
    using reference = const T&;
    using pointer = const T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    friend ForwardList<T>;
public:
    ConstIterator(const Node* ptr = nullptr);
    ConstIterator(const Iterator& other);
public:
    reference operator*() const;
    pointer operator->() const;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator==(const ConstIterator& other) const;
    bool operator!=(const ConstIterator& other) const;
private:
    const Node* m_ptr;
};

#include "forward_list_const_iterator.inl"

#endif  // FORWARD_LIST_CONST_ITERATOR_H_
