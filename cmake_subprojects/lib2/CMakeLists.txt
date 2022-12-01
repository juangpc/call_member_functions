cmake_minimum_required(VERSION 3.20)

project(Library2)

add_library(lib2_lib lib2.cpp)
target_include_directories(lib2_lib PUBLIC .)
