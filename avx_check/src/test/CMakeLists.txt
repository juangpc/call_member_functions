

set(SOURCES
    main.cpp
    sequentialComputation.cpp
    intrinsicsComputation.cpp
    utils.cpp
)

add_executable(avxCheck)

target_sources(avxCheck PRIVATE ${SOURCES})


set_target_properties( avxCheck
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/apps/${OUTPUT_NAME}"
)
set_property(TARGET avxCheck PROPERTY CXX_STANDARD 11)

# target_compile_definitions(avxCheck PUBLIC )
target_compile_options(avxCheck PRIVATE -mavx -mfma -O1)
