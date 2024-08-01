# begin of CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(fixed_point VERSION 0.0.1 DESCRIPTION "Library for manipulating binary representation and numerical precision formats")

# Include directories for common headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add library for precision
add_library(precision SHARED src/precision.c)
# Uncomment when ready to build quantization examples
# add_library(quantization SHARED src/quantization.c)
target_include_directories(precision PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add subdirectories for example categories
add_subdirectory(examples/fixed-point)
add_subdirectory(examples/floating-point)
# Uncomment when ready to build quantization examples
# add_subdirectory(examples/quantization)

# end of CMakeLists.txt
