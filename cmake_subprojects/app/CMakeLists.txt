cmake_minimum_required(VERSION 3.20)

project(Application)

add_executable(app app.cpp)
target_link_libraries(app lib1_lib lib2_lib)
