/*
    examples/extract_ieee_754.cpp

    This program demonstrates the process of extracting components of a floating-point
    number (sign, exponent, and mantissa) according to the IEEE 754 standard for
    single-precision floating-point format. It uses the example of representing the
    decimal number 6.25.

    Note: This is a simplified example and does not cover special cases like zero,
    infinity, NaN, or rounding considerations.
*/

#include <iostream>
#include <cstring>

// Define a struct to represent the components of a floating-point number
// Assuming 32-bit IEEE 754 single-precision format
struct MetaFloat {
    int sign;      // Bit 31: Sign bit
    int exponent;  // Bits 30-23: Exponent
    int fraction;  // Bits 22-0: Mantissa (Fraction)
};

// Function to extract the sign bit from a float
int extract_sign_bit(float float_value) {
    // Ensure that float and int have the same size for correct operation
    static_assert(sizeof(float) == sizeof(int), "Float and int must have the same size");

    int binary_representation;

    // Copy the bytes of the float into an integer for bit manipulation
    std::memcpy(&binary_representation, &float_value, sizeof(float));

    // Isolate and return the sign bit using bitwise operations
    return (binary_representation >> 31) & 1;
}

int main() {
    float my_float = 6.25f; // Specify the floating point number

    // Initialize an instance of MetaFloat to store extracted components
    MetaFloat meta_float;

    // Extract and store the sign bit
    meta_float.sign = extract_sign_bit(my_float);

    // Further extraction of exponent and fraction parts to be implemented

    // Output the extracted sign for verification
    std::cout << "Sign bit of " << my_float << ": " << meta_float.sign << std::endl;

    return 0;
}
