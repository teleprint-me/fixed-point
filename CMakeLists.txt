# Root CMakeLists.txt

# Specify the cmake minimum version.
cmake_minimum_required(VERSION 3.12)

# Specify the project information.
project("fixed_point" VERSION 0.0.1 DESCRIPTION "Library for manipulating binary representation and numerical precision formats")

find_package(PkgConfig REQUIRED)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(SOURCE_FILES src/floating_point.c)

# Include directories for common headers
include_directories(include src)

# Declare the library target; project depends on shared source files.
add_library(floating_point SHARED ${SOURCE_FILES})
# Link math library; link project against shared dependencies.
target_link_libraries(floating_point m)

# Set target properties
set_target_properties(
    floating_point PROPERTIES
    PUBLIC_HEADER include/fixed_point.h
    PUBLIC_HEADER include/floating_point.h
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

# Configure the directories to search for header files.
target_include_directories(floating_point PUBLIC include)

# Add library path for linking
link_directories(${CMAKE_BINARY_DIR})

# Add subdirectories for example categories
add_subdirectory(examples/fixed-point)
add_subdirectory(examples/floating-point)
