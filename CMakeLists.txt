# begin of CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
project(fixed_point VERSION 0.0.1 DESCRIPTION "Library for manipulating binary representation and numerical precision formats")

# Include directories for common headers
include_directories(${CMAKE_SOURCE_DIR}/include)

add_library(fixed_point SHARED 
    src/precision.c
    # src/quant.c
)

# Add subdirectories for example categories
add_subdirectory(examples/fixed-point)
add_subdirectory(examples/floating-point)
add_subdirectory(examples/quantization)
# end of CMakeLists.txt
