
add_library(simdCheck)

set(SOURCES
    simdCheck
)

target_sources(simdCheck PRIVATE ${SOURCES})


set_target_properties( simdCheck
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/out/apps/${OUTPUT_NAME}"
)
set_property(TARGET simdCheck PROPERTY CXX_STANDARD 17)

# target_compile_definitions(simdCheck PUBLIC )
target_compile_options(simdCheck PRIVATE -mavx -mfma -O3)

