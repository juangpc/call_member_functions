cmake_minimum_required(VERSION 3.2)
project(python_c_api)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Python COMPONENTS Interpreter Development)
cmake_path(GET Python_EXECUTABLE PARENT_PATH Python_BIN_DIR) 
# message(status "bin exec: " ${python_executable})
# message(status "bin dir : " ${python_bin_dir})
# message(status "p libs  : " ${python_libraries})

set(config_cmd_flags "--cflags")
execute_process(COMMAND ${Python_BIN_DIR}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}-config ${config_cmd_flags} 
  OUTPUT_VARIABLE Python_FLAGS)
# message(STATUS "FLAGS: " ${Python_FLAGS})

add_executable(python_extension main2.c)
target_link_libraries(python_extension PUBLIC python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR})
target_link_directories(python_extension PUBLIC ${Python_LIBRARY_DIRS})
target_include_directories(python_extension PUBLIC ${Python_INCLUDE_DIRS})
set_target_properties(python_extension PROPERTIES 
  OUTPUT_NAME "call"
  RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}
  )

separate_arguments(Python_FLAGS_NORM UNIX_COMMAND "${Python_FLAGS}")
target_compile_options(python_extension PUBLIC ${Python_FLAGS_NORM})

