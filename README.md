# Fixed-Point

## Overview

Fixed-Point is a lightweight Digital Signal Processing library written in pure
C, focusing on fixed-point precision, floating-point precision, and
quantization.

## Key Features

- **Comprehensive Header Files**: Provides essential fixed-point data types and
  arithmetic functions.
- **Practical Examples**: Demonstrative projects showcasing the use and benefits
  of fixed-point arithmetic.

## Getting Started

### Clone the Repository

Clone the repository with all submodules:

```sh
git clone --recurse-submodules -j$(nproc) \
    https://github.com/teleprint-me/fixed-point.git
cd fixed-point
```

### Update Submodules

To ensure all submodules are up to date, run:

```sh
git submodule update --init --recursive
```

### Build the Project

You can choose between automated and manual builds.

#### Automated Build

1. Make the build script executable:

   ```sh
   chmod +x auto_build.sh
   ```

2. Run the script to build, compile, and test:

   ```sh
   ./auto_build.sh
   ```

#### Manual Build

1. **Create the Build Environment:**

   ```sh
   cmake -B build -DCMAKE_BUILD_TYPE=Debug
   ```

2. **Compile the Code:**

   ```sh
   cmake --build build --config Debug -j$(nproc)
   ```

3. **Run Tests:**

   ```sh
   ctest --rerun-failed --output-on-failure --test-dir build
   ```

## Exploring the Codebase

After cloning, explore the `fixed-point` directory to understand the library's
structure:

- **Header Files**: Located in the `include` directory.
- **Examples**: Sample projects demonstrating usage in the `examples` directory.

```sh
ls include
ls examples
```

## Usage

To integrate the library into your C/C++ projects, include the header files:

```c
#include "fixed_point.h"
```

Refer to the example projects for guidance on using the library functions
effectively.

## References

### Mathematical Background

- [Calculus](https://leanpub.com/apexcalculus)
- [Discrete Mathematics](https://discrete.openmathbooks.org/dmoi3.html)
- [Statistics and Probability](https://stats.libretexts.org/Courses/Las_Positas_College/Math_40%3A_Statistics_and_Probability)
- [Linear Algebra](https://understandinglinearalgebra.org/home.html)
- [Digital Signal Processing](https://www.dspguide.com/)

### Programming References

- [C Programming Language Standard](https://www.open-std.org/JTC1/SC22/WG14/)
- [C Reference](https://en.cppreference.com/w/c)
- [CMake Reference](https://cmake.org/cmake/help/latest/)
- [Bash Reference](https://www.gnu.org/software/bash/manual/html_node/index.html)

## License

This project is licensed under the AGPL License. See the [LICENSE](LICENSE) file
for details.
