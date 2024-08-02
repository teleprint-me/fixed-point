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

### auto-build
- **`auto-build` Script**: Automatically builds everything. It is a symlink to `build.sh`.

```sh
./auto-build
```

### build.sh

- **`build.sh` Script**: Cleans the build environment if a build path exists or builds using CMake if it does not.

```sh
chmod +x build.sh
./build.sh
```

This script performs the following steps:

1. **Clean Environment**: If a build path exists, it is cleaned.
2. **Build with CMake**: If the build path does not exist, it builds the project.

### Manually building with cmake

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

### Manually building with gcc

Manually build with gcc is a bit more involved, but it's straightforward once the steps are understood.

This really depends on what and how you want to build, but this is typically what I did to initially compile the fixed-point example programs.

It should be noted that fixed-point is currently a stand-alone header and does not require any compilation, linking, exporting, or any other steps. It's a standalone header. This may change in the future, though.

We can use a floating-point example which is a more complex build process as a example to ensure we're thorough throughout the process.

Let's say we want to setup the Simple IEEE-754 example program in the `examples/floating-point` path.

We'll need a few components first.

- `src/floating_point.c`: The primary shared library
- `examples/floating-point/simple_ieee_754.cpp`: The example program
- `build/libfloating_point.so`: (Optional) we can link against the shared object, but this isn't necessary. I include this to be comprehensive.

We need to build with `g++`, not `gcc`, because the source file is a C++ source file and the compilation will fail otherwise.

```sh
g++ src/floating_point.c examples/floating-point/simple_ieee_754.cpp -o simple -lm
```

Then we can run the program.

```sh
./simple
```

There are no help options as the example program isn't meant to be a end-user tool, rather a process of how to break down the 32-bit implementation into it's simplest components for supporting IEEE-754 floating-point numbers. It's more of a proof of concept than anything else.

To link against a shared object, we'll need to build the shared object first. Note that the auto-build script does this for us already, but this is good to understand regardless.

```sh
g++ 
```

If we attempt to execute the program without doing anything else, we will get an error.

```sh
./simple
./simple: error while loading shared libraries: libfloating_point.so.0: cannot open shared object file: No such file or directory
```

This is because the environment does not know where look for the shared object. We need to specify it somehow. To avoid getting lost in the weeds, we can take a shortcut and simply prepend and define the `LD_LIBRARY_PATH` ahead of time.

```sh
LD_LIBRARY_PATH='.' ./simple
```

If the shared obect is in another path, say build, then we specify that path instead.

```sh
LD_LIBRARY_PATH='build' ./simple
```

This should allow us to execute the binary now. https://gcc.gnu.org/ is an excellent resource. Both https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html and https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_dynamic_or_shared.html shed more light upon the details of how this works in more detail.

## Build Path Structure

Compiled executables are organized similarly to the examples structure:

- `build/fixed-point`
- `build/floating-point`
- `build/quantization`

Currently, only `fixed-point` builds successfully. The `floating-point` examples are still being developed, and research on `quantization` is ongoing. Combining these tools effectively can provide powerful utilities, which aligns with the core motivation behind the fixed-point library.

## Summary

TODO
