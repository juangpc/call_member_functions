cmake_minimum_required(VERSION 3.20)

project(ipc_thread)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
set(THREADS_PREFER_PTHREAD_FLAG ON)
set(CMAKE_CXX_STANDARD 11)

add_executable(process1 main1.cpp)
add_executable(process2 main2.cpp)





