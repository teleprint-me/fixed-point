# Quantization CMakeLists.txt

# Add quantization related examples
set(QUANTIZATION_SOURCES
    simple_quant.cpp
)

# Create executables for quantization examples
foreach(src ${QUANTIZATION_SOURCES})
    get_filename_component(target ${src} NAME_WE)
    add_executable(${target} ${src})
    # target_link_libraries(${target} quantization_lib) # no library currently exists for this, yet...
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/quantization)
endforeach()
