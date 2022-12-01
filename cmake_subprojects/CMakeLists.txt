cmake_minimum_required(VERSION 3.20)

project(MainProject)

set(CMAKE_C_COMPILER "/usr/local/Cellar/llvm/13.0.1_1/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/Cellar/llvm/13.0.1_1/bin/clang")


add_subdirectory(app)
add_subdirectory(lib1)
add_subdirectory(lib2)
# add_subdirectory(lib3)

