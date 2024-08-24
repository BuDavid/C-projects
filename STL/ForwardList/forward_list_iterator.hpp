#ifndef FORWARD_LIST_ITERATOR_H_
#define FORWARD_LIST_ITERATOR_H_

#include "forward_list.hpp"
#include <iterator>

template <typename T>
class ForwardList<T>::Iterator {
public:
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    friend class ForwardList<T>::ConstIterator;
    friend class ForwardList<T>;
public:
    Iterator(Node* ptr = nullptr);
public:
    reference operator*() const;
    pointer operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
private:
    Node* m_ptr;
};

#include "forward_list_iterator.inl"

#endif  // FORWARD_LIST_ITERATOR_H_
