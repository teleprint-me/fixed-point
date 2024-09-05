# Fixed-Point

## Overview

Fixed-Point is a library for Digital Signal Processing with a primary focus on fixed-point precision, floating-point precision, and quantization in pure C.

## Key Features

- **Comprehensive Header File**: Equipped with essential fixed-point data types
  and arithmetic functions.
- **Practical Examples**: Demonstrative projects showcasing the application and
  advantages of fixed-point arithmetic.
- **AGPL License**: Licensed under the AGPL, ensuring freedom to use, modify,
  and distribute with adherence to its terms.

## Getting Started

1. **Clone the Repository**: Start by cloning the repository to your local
   machine:

   ```sh
   git clone https://github.com/teleprint-me/fixed-point.git
   ```

2. **Explore the `fixed-point` Directory**: After cloning, navigate to the
   `fixed-point` directory. Here, you can find the header files in the `include`
   directory and example projects in the `examples` directory:

   ```sh
   cd fixed-point
   ls include
   ls examples
   ```

3. **Customize and Build**: Dive into the examples to understand how the library
   works. Feel free to modify and experiment with the code to fit your needs:

   ```sh
   vim examples
   ```

## Building the Library

1. **Review the Build Script**: Familiarize yourself with the `build.sh` script,
   which streamlines the library's compilation process.

   ```sh
   vim build.sh
   ```

2. **Compile the Library**: Execute the `build.sh` script to compile the
   library.

   ```sh
   ./build.sh
   ```

3. **Access Compiled Binaries**: The compiled binaries are organized by category
   and can be found in their respective directories.

   ```sh
   ls build/fixed-point
   ls build/floating-point
   ```

4. **Execute Compiled Binaries**: Run the compiled binaries from the respective
   directories.

   ```sh
   ./build/fixed-point/float_to_fixed
   ./build/floating-point/simple_ieee_754
   ```

## Usage

Integrate the library into your C/C++ projects with ease:

```c
#include "fixed_point.h"
```

For in-depth instructions on using the library effectively, refer to the
accompanying documentation and examples.

## Contributing

Contributions are highly encouraged! Feel free to contribute ideas, bug fixes,
or enhancements by submitting issues and pull requests.

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
