
add_library(calls STATIC src/calls.cpp)
target_include_directories(calls PUBLIC include) 

add_library(calls_shared SHARED src/calls.cpp)
target_include_directories(calls_shared PUBLIC include)

