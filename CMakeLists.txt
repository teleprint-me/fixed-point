cmake_minimum_required(VERSION 3.12)

# Project Name
project(fixed_point)

# Add executable targets for your examples
add_executable(float_to_fixed examples/float_to_fixed.cpp)
add_executable(fixed_arithmetic examples/fixed_arithmetic.cpp)
add_executable(extract_sign_bit examples/extract_sign_bit.cpp) # Add this line

# Optionally set the output directories for the executables
set_target_properties(float_to_fixed PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
set_target_properties(fixed_arithmetic PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
set_target_properties(extract_sign_bit PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples)
