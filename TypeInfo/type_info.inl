#include "type_info.hpp"

template <typename U>
void TypeInfo::val_type(U&& val) const {
    get_const_type(std::forward<U>(val));
    get_val_type(std::forward<U>(val));
    get_ref_type(std::forward<U>(val));
}

template <typename U>
void TypeInfo::get_const_type(U&& val) const {
    if (std::is_const<std::remove_reference_t<U>>::value) {
        std::cout << "const ";
    }
}

template <typename U>
void TypeInfo::get_val_type(U&& val) const {
    std::string type = typeid(val).name();
    std::cout << demangle(type) << " ";
}

template <typename U>
void TypeInfo::get_ref_type(U&& val) const {
    if (std::is_lvalue_reference<decltype(val)>::value) {
        std::cout << "lvalue" << std::endl;
    } else {
        std::cout << "rvalue" << std::endl;
    }
}

std::string TypeInfo::demangle(const std::string& name) const {
    int status = 0;
    char* demangled = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
    std::string result(status ? name : demangled);
    
    std::free(demangled);
    return result;
}

