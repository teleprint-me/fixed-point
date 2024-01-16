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
#include <bitset>

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

// Function to extract the exponent bits from a float
int extract_exponent_bits(float float_value) {
    static_assert(sizeof(float) == sizeof(int), "Float and int must have the same size");

    int binary_representation;
    std::memcpy(&binary_representation, &float_value, sizeof(float));

    // Extract the exponent bits (bits 30-23) by masking and shifting
    return (binary_representation >> 23) & 0xFF; // Assuming 32-bit single-precision
}

// Function to extract the mantissa bits from a float
int extract_mantissa_bits(float float_value) {
    static_assert(sizeof(float) == sizeof(int), "Float and int must have the same size");

    int binary_representation;
    std::memcpy(&binary_representation, &float_value, sizeof(float));

    // Extract the mantissa bits (bits 22-0) by masking
    return binary_representation & 0x7FFFFF; // Assuming 32-bit single-precision
}

// Function to extract all components of a floating-point number
MetaFloat extract_float_metadata(float float_value) {
    MetaFloat meta_float;
    
    // Extract the sign bit
    meta_float.sign = extract_sign_bit(float_value);

    // Extract the exponent bits
    meta_float.exponent = extract_exponent_bits(float_value);

    // Extract the mantissa bits
    meta_float.fraction = extract_mantissa_bits(float_value);

    return meta_float;
}

// Function to convert an integer to a binary string
std::string to_binary_string(int value, int bits) {
    return std::bitset<32>(value).to_string().substr(32 - bits);
}

int main() {
    float my_float = 6.25f;

    // Extract all components of the floating-point number
    MetaFloat meta_float = extract_float_metadata(my_float);

    // Output the extracted components for verification
    std::cout << "Floating Point Representation of " << my_float << ":\n";
    std::cout << "Sign Bit: " << meta_float.sign << " (Binary: " << to_binary_string(meta_float.sign, 1) << ")\n";
    std::cout << "Exponent Bits: " << meta_float.exponent << " (Binary: " << to_binary_string(meta_float.exponent, 8) << ")\n";
    std::cout << "Mantissa Bits: " << meta_float.fraction << " (Binary: " << to_binary_string(meta_float.fraction, 23) << ")\n";

    return 0;
}
