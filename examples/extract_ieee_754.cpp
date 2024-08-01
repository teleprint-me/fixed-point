/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/extract_ieee_754.cpp
 *
 * This program demonstrates the process of extracting components of a floating-point
 * number (sign, exponent, and mantissa) according to the IEEE 754 standard for
 * single-precision floating-point format. It uses the example of representing the
 * decimal number 6.25.
 *
 * Note: This is a simplified example and does not cover special cases like zero,
 * infinity, NaN, or rounding considerations. This will be implemented in the future.
 */

#include <bitset>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <iostream>

// Define a struct to represent the components of a floating-point number
// Assuming 32-bit IEEE 754 single-precision format
typedef struct {
    uint32_t sign;          // Bit 31: Sign bit
    uint32_t exponent;      // Bits 30-23: Exponent
    uint32_t mantissa;      // Bits 22-0: Mantissa (Fraction)
    uint32_t bias;          // Add bias for the format
    uint32_t mask_sign;     // Mask for the sign
    uint32_t mask_exponent; // Mask for the exponent
    uint32_t mask_mantissa; // Mask for the mantissa
} float_meta_t;

typedef union {
    uint32_t bits;
    float    value;
} float32_t;

// float to integer
uint32_t encode_float32(float value) {
    float32_t data;
    data.value = value;
    return data.bits;
}

// integer to float
float decode_float32(uint32_t bits) {
    float32_t data;
    data.bits = bits;
    return data.value;
}

// Function to extract the sign bit from a float
uint32_t extract_sign_bit(uint32_t bits) {
    /**
     * @important This is not a docstring, these are valuable notes.
     * @important DO NOT REMOVE THESE NOTES.
     * THEY MAY BE IMPROVED, BUT MAY **NOT** BE REMOVED.
     *
     * @note The sign bit is always the most significant bit.
     *       In a n-bit value, this is always the left-most bit
     *       in the digit sequence and is always a width of 1.
     *       The mask used to extract the bit is 0x1.
     *       0x1 maps to (1) and flips any falsy values to 0.
     *
     * sign exponent    mantissa
     * (1) (0000 0000) (000 0000 0000 0000 0000 0000)
     *
     * Where:
     * - (1) is the sign bit
     * - (0000 0000) is the exponent
     * - (000 0000 0000 0000 0000 0000) is the mantissa
     */

    // Isolate and return the sign bit using bitwise operations
    return (bits >> 31) & 1;
}

// Function to extract the exponent bits from a float
uint32_t extract_exponent_bits(uint32_t bits) {
    /**
     * @important This is not a docstring, these are valuable notes.
     * @important DO NOT REMOVE THESE NOTES.
     * THEY MAY BE IMPROVED, BUT MAY **NOT** BE REMOVED.
     *
     * @note The exponent bits always come after the sign bit.
     *       The number of bits in the exponent is a dependent variable.
     *       e.g. If the width is 32-bits, then the exponent is 8-bits.
     *       The mask used to extract the bits is 0xFF.
     *       0xFF maps to (1111 1111) and flips any falsy values to 0.
     *
     * sign exponent    mantissa
     * (0) (1111 1111) (000 0000 0000 0000 0000 0000)
     *
     * Where:
     * - (0) is the sign bit
     * - (1111 1111) is the exponent
     * - (000 0000 0000 0000 0000 0000) is the mantissa
     */

    // Extract the exponent bits (bits 30-23) by masking and shifting
    return (bits >> 23) & 0xFF; // Assuming 32-bit single-precision
}

uint32_t uint32_pow(uint32_t base, uint32_t exponent) {
    uint32_t result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result *= base;
        }
        base      *= base;
        exponent >>= 1;
    }
    return result;
}

uint32_t calculate_bias(uint32_t width) {
    return uint32_pow(2, width - 1) - 1;
}

int32_t convert_exponent(uint32_t bits, uint32_t width_src, uint32_t width_dest) {
    uint32_t bias_src      = calculate_bias(width_src);
    uint32_t bias_dest     = calculate_bias(width_dest);
    uint32_t exponent_mask = (1 << width_src) - 1;
    int32_t  exponent      = ((bits >> (32 - width_src)) & exponent_mask) - bias_src;
    return exponent + bias_dest;
}

// Function to extract the mantissa bits from a float
uint32_t extract_mantissa_bits(uint32_t bits) {
    /**
     * @important This is not a docstring, these are valuable notes.
     * @important DO NOT REMOVE THESE NOTES.
     * THEY MAY BE IMPROVED, BUT MAY **NOT** BE REMOVED.
     *
     * @note The mantissa bits always come after the exponent bits.
     *       The number of bits in the mantissa is a dependent variable.
     *       e.g. If the width is 32-bits, then the mantissa is 23-bits.
     *       The mask used to extract the bits is 0x7FFFFF.
     *       0x7FFFFF maps to (111 1111 1111 1111 1111 1111) and flips any
     *       falsy values to 0.
     *
     * sign exponent    mantissa
     * (0) (0000 0000) (111 1111 1111 1111 1111 1111)
     *
     * Where:
     * - (0) is the sign bit
     * - (0000 0000) is the exponent
     * - (111 1111 1111 1111 1111 1111) is the mantissa
     */

    // Extract the mantissa bits (bits 22-0) by masking
    return bits & 0x7FFFFF; // Assuming 32-bit single-precision
}

// Function to extract all components of a floating-point number
float_meta_t extract_float_metadata(float value) {
    float_meta_t meta_float;
    uint32_t     bits = encode_float32(value);

    meta_float.sign     = extract_sign_bit(bits);
    meta_float.exponent = extract_exponent_bits(bits);
    meta_float.mantissa = extract_mantissa_bits(bits);

    return meta_float;
}

// return some kind of flexible type?
// maybe start off with 32-bit just to get an idea of how this might work
// uint32_t extract_binary_representation(float_meta_t meta, (void*) (float_meta_t meta)) {
//
// Ensure that float and int have the same size for correct operation
// static_assert(sizeof(float) == sizeof(uint32_t), "float and uint32_t must have the same size");
//
// return (meta.sign) | (meta.exponent) | (meta.mantissa);
// }

// Function to convert an integer to a binary string
std::string to_binary_string(int value, int bits) {
    return std::bitset<32>(value).to_string().substr(32 - bits);
}

int main() {
    float pi = 3.141592653589793f;

    // Extract all components of the floating-point number
    float_meta_t meta = extract_float_metadata(pi);
    // uint32_t     bits = extract_binary_representation(meta, 8, 23);

    // Output the extracted components for verification
    // this doesn't show precision or allow for control of precision like printf() does
    // how do i do this?
    std::cout << "Floating Point Representation of ";
    std::cout << std::fixed << std::setprecision(7) << pi << ":\n";
    std::cout << "Sign Bit: " << meta.sign // sign
              << " (Binary: " << to_binary_string(meta.sign, 1) << ")\n";
    std::cout << "Exponent Bits: " << meta.exponent // integer
              << " (Binary: " << to_binary_string(meta.exponent, 8) << ")\n";
    std::cout << "Mantissa Bits: " << meta.mantissa // fraction
              << " (Binary: " << to_binary_string(meta.mantissa, 23) << ")\n";

    // std::cout << "Bit Representation: " << to_binary_string(bits, 32) << "\n";

    return 0;
}
