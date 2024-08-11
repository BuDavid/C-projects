cmake_minimum_required(VERSION 3.1)

project(SharedPointer)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include src)

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp 
)
