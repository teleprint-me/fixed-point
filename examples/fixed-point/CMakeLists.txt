# begin of examples/fixed-point/CMakeLists.txt
# Add fixed-point related examples
set(FIXED_POINT_SOURCES
    fixed_arithmetic.cpp
    float_to_fixed.cpp
)

# Create executables for fixed-point examples
foreach(src ${FIXED_POINT_SOURCES})
    get_filename_component(target ${src} NAME_WE)
    add_executable(${target} ${src})
    # fixed-point is a header library, but might expand... to be decided.
    # currently, there is nothing to compile as it is header-only at the moment.
    # target_link_libraries(${target} fixed_point_lib)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/fixed-point)
endforeach()
# end of examples/fixed-point/CMakeLists.txt
