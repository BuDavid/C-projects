cmake_minimum_required(VERSION 3.0)
project(Matrix)
add_executable(main main.cpp matrix.cpp)
target_compile_options(main PRIVATE -g)
