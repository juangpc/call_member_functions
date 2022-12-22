project(python_lib VERSION 0.1 
  DESCRIPTION "Initial implementation of a python interpreter called on demand"
  )

add_library(python_lib SHARED 
  src/python1.cpp
  )

set_target_properties(python_lib PROPERTIES
  VERSION ${PROJECT_VERSION}
  PUBLIC_HEADER include/python_lib.hpp
  )
# target_link_libraries(python_lib calls)
target_include_directories(python_lib
  PUBLIC include
  PUBLIC /opt/anaconda3/include/python3.9
  )

