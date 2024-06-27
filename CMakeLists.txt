cmake_minimum_required(VERSION 3.12)

# Project Name
project(fixed_point)

set(SOURCE_TARGETS
    float_to_fixed
    fixed_arithmetic
    extract_sign_bit
    extract_ieee_754
    simple_ieee_754
    simple_half
    maratyszcza
)

# Add executable targets for your examples
foreach(target ${SOURCE_TARGETS})
    add_executable(${target} examples/${target}.cpp)
endforeach()

# List of your executable targets
set(EXECUTABLE_TARGETS
    float_to_fixed
    fixed_arithmetic
    extract_sign_bit
    extract_ieee_754
    simple_ieee_754
    simple_half
    maratyszcza
)

# Loop through the target names and set the output directory for each
foreach(target ${EXECUTABLE_TARGETS})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
endforeach()
