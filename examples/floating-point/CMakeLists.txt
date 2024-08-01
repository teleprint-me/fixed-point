# begin of examples/floating-point/CMakeLists.txt

# Add floating-point related examples
set(FLOATING_POINT_SOURCES
    extract_exponent_bias.cpp
    extract_ieee_754.cpp
    extract_sign_bit.cpp
    google_bfloat.cpp
    ieee_754_32bit.cpp
    maratyszcza.cpp
    simple_half.cpp
    simple_ieee_754.cpp
)

# Create executables for floating-point examples
foreach(src ${FLOATING_POINT_SOURCES})
    get_filename_component(target ${src} NAME_WE)
    add_executable(${target} ${src})
    target_link_libraries(${target} precision)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/floating-point)
endforeach()

# end of examples/floating-point/CMakeLists.txt
