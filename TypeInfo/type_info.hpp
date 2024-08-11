#ifndef TYPEINFO_H_
#define TYPEINFO_H_

#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <cxxabi.h>
#include <cstdlib>

class TypeInfo {
public:
    template <typename U>
    void val_type(U&& val) const;
private:
    template <typename U>
    void get_ref_type(U&& val) const;
    template <typename U>
    void get_val_type(U&& val) const;
    template <typename U>
    void get_const_type(U&& val) const;
    std::string demangle(const std::string& name) const;
};

#include "type_info.inl"

#endif  // TYPEINFO_H_
