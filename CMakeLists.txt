# Root CMakeLists.txt

cmake_minimum_required(VERSION 3.14)
project(fixed_point VERSION 0.1.0 DESCRIPTION "ANSI C library for Digital Signal Processing")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_subdirectory(mods/float_is_close)

add_library(fixed_point SHARED src/floating_point.c)

set_target_properties(
    fixed_point
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER include/fixed_point.h
    PUBLIC_HEADER include/floating_point.h
)

target_include_directories(fixed_point PUBLIC include)
target_link_libraries(fixed_point m float_is_close)

link_directories(${CMAKE_BINARY_DIR})

add_subdirectory(examples/fixed-point)
add_subdirectory(examples/floating-point)
