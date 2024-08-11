cmake_minimum_required(VERSION 3.1)

project(Queen)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

set(TABLE_DIR ${SOURCE_DIR}/../Table)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include ${TABLE_DIR})

add_executable(
    ${PROJECT_NAME} 
    src/main.cpp 
    src/qtable.cpp 
    src/queen.cpp 
    ${TABLE_DIR}/table.cpp
)
