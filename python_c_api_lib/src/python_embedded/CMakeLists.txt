
add_executable(python_embedded main.cpp)

target_link_libraries(python_embedded python3.9)
target_link_directories(python_embedded
  PUBLIC "/opt/anaconda3/lib")

target_include_directories(python_embedded
  PUBLIC /opt/anaconda3/include/python3.9
  )

set_property(TARGET python_embedded PROPERTY CMAKE_CXX_STANDARD 17)

