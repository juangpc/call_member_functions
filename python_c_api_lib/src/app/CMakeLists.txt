
add_executable(hellos main.cpp)

target_link_libraries(hellos calls)

set_property(TARGET hellos PROPERTY CMAKE_CXX_STANDARD 17)

