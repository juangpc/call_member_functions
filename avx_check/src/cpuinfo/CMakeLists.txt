

add_executable(cpuinfo)

set(sources
    main.cpp
)

target_sources(cpuinfo PRIVATE ${sources})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY)

set_target_properties(cpuinfo
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/apps/${OUTPUT_NAME}"
)
set_property(TARGET cpuinfo PROPERTY CXX_STANDARD 11)
