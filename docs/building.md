# Building Fixed-Point Library

The fixed-point library is designed as a library, rather than a standalone program. Example programs are included for demonstration purposes and convenience.

Although I typically prefer using binaries directly in shell scripts or Makefiles, I've started learning CMake for this project despite its complexity. While CMake is powerful, its depth can be overwhelming. The core library is written in C, with example programs sometimes using limited C++ features. Despite C++'s advanced capabilities, especially in generics, metaprogramming, and the Standard Template Library (STL), I find C’s simplicity preferable.

## Repository Structure

The repository is organized for flexibility:

- **Root Path**: Contains the CMake build script for the shared object, located in `fixed-point/CMakeLists.txt`.
- **Examples Path**:
  - `examples/fixed-point`: Examples related to `include/fixed_point.h`.
  - `examples/floating-point`: Examples related to `include/floating_point.h` and `floating_point.c`.
  - `examples/quantization`: Placeholder for signal processing programs; currently under development.

Each category is in early development, with some programs incomplete or non-functional, particularly in the quantization area.

## Convenience Scripts

These scripts streamline the build process, assuming necessary dependencies (CMake, clang, gcc, g++, and standard libraries) are installed. The scripts are tailored for Linux environments.

### `auto-build`

Automatically builds all components. It is a symlink to `build.sh`.

```sh
./auto-build
```

### `build.sh`

Handles environment cleanup and builds the project using CMake.

```sh
chmod +x build.sh
./build.sh
```

#### Steps:

1. **Clean Environment**: If a build path exists, it is cleaned.
2. **Build with CMake**: If the build path does not exist, it creates it and builds the project.

### Manually Building with CMake

By default, the build type is set to Debug:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

To enable verbose output for troubleshooting:

```sh
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON
```

To build the project, you can use the `-j` flag to specify the number of parallel jobs. Using `nproc` automatically sets this to the number of available processors:

```sh
cmake --build build --config Debug -j $(nproc)
```

### Manually Building with gcc

Building with `gcc` is straightforward but requires understanding the specific components involved.

Currently, `fixed-point` is a standalone header, requiring no compilation. For demonstration, let’s consider a floating-point example in the `examples/floating-point` directory.

#### Example: Building a Simple IEEE-754 Example

Components needed:
- `src/floating_point.c`: The shared library source.
- `examples/floating-point/simple_ieee_754.cpp`: The example program.
- `build/libfloating_point.so`: (Optional) for linking against the shared object.

```sh
g++ src/floating_point.c examples/floating-point/simple_ieee_754.cpp -o simple -lm
```

Run the program:

```sh
./simple
```

For linking against a shared object:

1. Build the shared object (handled by `auto-build`):

```sh
g++ src/floating_point.c -shared -o build/libfloating_point.so
```

2. Specify the path for the shared object:

```sh
LD_LIBRARY_PATH='build' ./simple
```

For more details, refer to [GCC Link Options](https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html) and [GCC Shared Libraries](https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dynamic_or_shared.html).

## Build Path Structure

Compiled executables are organized in:

- `build/fixed-point`
- `build/floating-point`
- `build/quantization`

Currently, only the `fixed-point` builds are functional. The `floating-point` examples are under development, and research on `quantization` is ongoing. Integrating these components can lead to powerful utilities, aligning with the library's core purpose.

## Summary

TODO
