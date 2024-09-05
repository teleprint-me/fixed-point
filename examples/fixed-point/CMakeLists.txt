# Fixed-Point CMakeLists.txt

# Add fixed-point related examples
set(FIXED_POINT_SOURCES
    fixed_arithmetic
    float_to_fixed
)

# Create executables for fixed-point examples
# Loop over each example and create an executable
foreach(example IN LISTS FIXED_POINT_SOURCES)
    add_executable(${example} ${PROJECT_SOURCE_DIR}/examples/fixed-point/${example}.cpp)
    target_link_libraries(${example} fixed_point)
    target_include_directories(${example} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    set_target_properties(${example} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/fixed-point)
endforeach()
