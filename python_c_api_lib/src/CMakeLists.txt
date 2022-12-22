cmake_minimum_required(VERSION 3.2)

project(cpp_python_integratio)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_GENERATOR "Ninja")

add_subdirectory(lib)
add_subdirectory(app)
add_subdirectory(python_embedded)


