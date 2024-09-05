# Floating-Point CMakeLists.txt

# Add floating-point related examples
set(FLOATING_POINT_SOURCES
    extract_exponent_bias
    extract_ieee_754
    extract_sign_bit
    google_bfloat
    ieee_754_32bit
    maratyszcza
    simple_half
    simple_ieee_754
)

# Create executables for fixed-point examples
# Loop over each example and create an executable
foreach(example IN LISTS FLOATING_POINT_SOURCES)
    add_executable(${example} ${PROJECT_SOURCE_DIR}/src/floating_point.c ${PROJECT_SOURCE_DIR}/examples/floating-point/${example}.cpp)
    target_link_libraries(${example} fixed_point)
    target_include_directories(${example} PRIVATE ${PROJECT_SOURCE_DIR}/include)
    set_target_properties(${example} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/floating-point)
endforeach()
