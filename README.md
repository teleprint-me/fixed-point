# Fixed-Point Arithmetic Library

## Overview

The Fixed-Point Arithmetic Library is a valuable resource for mastering and implementing fixed-point arithmetic in C and C++. This library excels in handling real-world applications that demand precise numerical computations while providing a more efficient alternative to floating-point operations.

## Key Features

- **Comprehensive Header File**: Equipped with essential fixed-point data types and arithmetic functions.
- **Practical Examples**: Demonstrative projects showcasing the application and advantages of fixed-point arithmetic.
- **AGPL License**: Licensed under the AGPL, ensuring freedom to use, modify, and distribute with adherence to its terms.

## Getting Started

1. **Clone the Repository**: Start by cloning the repository to your local machine:

    ```sh
    git clone https://github.com/teleprint-me/fixed-point.git
    ```

2. **Explore the `fixed-point` Directory**: After cloning, navigate to the `fixed-point` directory. Here, you can find the header files in the `include` directory and example projects in the `examples` directory:

    ```sh
    cd fixed-point
    ls include
    ls examples
    ```

3. **Customize and Build**: Dive into the examples to understand how the library works. Feel free to modify and experiment with the code to fit your needs:

    ```sh
    vim examples
    ```

## Building the Library

1. **Review the Build Script**: Familiarize yourself with the `build.sh` script, which streamlines the library's compilation process.

    ```sh
    vim build.sh
    ```

2. **Compile the Library**: Execute the `build.sh` script to compile the library.

    ```sh
    ./build.sh
    ```

3. **Access Compiled Binaries**: Locate and run the compiled binaries.

    ```sh
    ls build/examples/
    ./build/examples/float_to_fixed
    ```

## Usage

Integrate the library into your C/C++ projects with ease:

```c
#include "fixed_point.h"
```

For in-depth instructions on using the library effectively, refer to the accompanying documentation and examples.

## License

This project is licensed under the AGPL. For detailed licensing terms, please refer to the [LICENSE](LICENSE) file.

## Contributing

Contributions are highly encouraged! Feel free to contribute ideas, bug fixes, or enhancements by submitting issues and pull requests.
