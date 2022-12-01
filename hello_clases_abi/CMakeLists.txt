cmake_minimum_required(VERSION 3.21)

set(CMAKE_C_COMPILER )

project(hello_clases_abi)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O0 -Wall -Wextra")

add_executable(hello_clases_abi main.cpp)
