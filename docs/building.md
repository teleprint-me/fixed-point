# Building Fixed-Point Library

The fixed-point library is primarily a library, not a standalone program. Example programs are provided for convenience and demonstration purposes.

Although I generally prefer using binaries directly in shell scripts or Makefiles, I am making an effort to learn CMake, despite its complexity. CMake is powerful but can be overwhelming due to its depth.

The fixed-point library is written in pure C, while the example programs may use limited C++ features. While C++ offers many advanced features, I find its complexity—especially in generics, meta-programming, and the Standard Template Library—challenging. I prefer C for its simplicity, even though C++ supports object-oriented programming, which I value.

## Repository Structure

The repository is designed to provide maximum flexibility:

- **Root Path**: Contains the CMake build script for the shared object, located in `fixed-point/CMakeLists.txt`.

- **Examples Path**:
  - `examples/fixed-point`: Contains examples related to `include/fixed_point.h`.
  - `examples/floating-point`: Contains examples related to `include/floating_point.h` and `floating_point.c`.
  - `examples/quantization`: Planned for signal processing programs; currently a work in progress.

Each category is still in early development, with some programs incomplete or non-functional, especially in the quantization area.

## Convenience Scripts

I have created convenience scripts to streamline the build process. These scripts assume you have the necessary dependencies (CMake, clang, gcc, g++, and standard libraries) and are tailored for Linux environments.

- **`auto-build` Script**: Automatically builds everything. It is a symlink to `build.sh`.

  ```sh
  ./auto-build
  ```

- **`build.sh` Script**: Cleans the build environment if a build path exists or builds using CMake if it does not.

  ```sh
  chmod +x build.sh
  ./build.sh
  ```

  This script performs the following steps:

  1. **Clean Environment**: If a build path exists, it is cleaned.
  2. **Build with CMake**: If the build path does not exist, it builds the project.

  By default, the build type is set to Debug:

  ```sh
  cmake -B build -DCMAKE_BUILD_TYPE=Debug
  ```
  
  If there are compilation issues, increasing verbosity can help. To enable verbose output while configuring the build, use:

  ```sh
  cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_VERBOSE_MAKEFILE=ON
  ```
  
  After configuring, build the project. To speed up compilation, you can use the `-j` flag to specify the number of parallel jobs. By default, this is set to 8, but you can adjust it according to your CPU. A convenient way to automatically set this to the number of available processors is to use `nproc`:

  ```sh
  cmake --build build --config Debug -j $(nproc)
  ```

  The `auto-build` script is generally sufficient for rapid development cycles.

## Build Path Structure

Compiled executables are organized similarly to the examples structure:

- `build/fixed-point`
- `build/floating-point`
- `build/quantization`

Currently, only `fixed-point` builds successfully. The `floating-point` examples are still being developed, and research on `quantization` is ongoing. Combining these tools effectively can provide powerful utilities, which aligns with the core motivation behind the fixed-point library.

## Summary

TODO
