cmake_minimum_required(VERSION 3.20)

project(Library1)

add_library(lib1_lib lib1.cpp)
target_include_directories(lib1_lib PUBLIC .)


