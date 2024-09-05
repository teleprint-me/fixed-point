/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/floating-point/ieee_754_32bit.cpp
 *
 * @ref https://ieeexplore.ieee.org/document/8766229
 * @ref /usr/include/c10/util/half.h
 * @ref https://www.geeksforgeeks.org/ieee-standard-754-floating-point-numbers/
 * @ref https://github.com/Maratyszcza/FP16
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.141592653589793f

// 32-bit floating point (standard float)
typedef union {
    uint32_t bits;
    float    value;
} float32_t;

// Standard half-precision (IEEE 754)
typedef uint16_t float16_t;

uint32_t encode_float(float value);
float    decode_float(uint32_t bits);

float16_t encode_float16(float value);
float     decode_float16(float16_t bits);

// Function to encode a float into its IEEE-754 binary32 representation
uint32_t encode_float(float value) {
    float32_t f32;
    f32.value = value;
    return f32.bits;
}

// Function to decode an IEEE-754 binary32 representation into a float
float decode_float(uint32_t bits) {
    float32_t f32;
    f32.bits = bits;
    return f32.value;
}

/*
 * Convert a 32-bit floating-point number in IEEE single-precision format to a 16-bit floating-point
 * number in IEEE half-precision format, in bit representation.
 */
uint16_t encode_float16(float value) {
    // Use a uint32_t bit representation of the float values

    // Constants for scaling to handle large and small values
    const float scale_to_inf  = decode_float(UINT32_C(0x77800000)); // Upper bound
    const float scale_to_zero = decode_float(UINT32_C(0x08800000)); // Lower bound

    // Saturate the input value towards infinity and scale back to half-precision range
    const float saturated_f = fabsf(value) * scale_to_inf;
    float       base        = saturated_f * scale_to_zero;

    // Get the 32-bit representation of the input float
    const uint32_t f      = encode_float(value);
    // Shift left by one bit (equivalent to multiplying by 2)
    const uint32_t shl1_f = f + f;
    // Extract the sign bit
    const uint32_t sign   = f & UINT32_C(0x80000000);
    // Extract the exponent bits and adjust for subnormal numbers
    uint32_t       bias   = shl1_f & UINT32_C(0xFF000000);
    if (bias < UINT32_C(0x71000000)) {
        bias = UINT32_C(0x71000000);
    }

    // Adjust the base using the bias and convert back to float
    base                         = decode_float((bias >> 1) + UINT32_C(0x07800000)) + base;
    // Get the 32-bit integer representation of the adjusted base
    const uint32_t bits          = encode_float(base);
    // Extract bits for half-precision format
    const uint32_t exp_bits      = (bits >> 13) & UINT32_C(0x00007C00);
    const uint32_t mantissa_bits = bits & UINT32_C(0x00000FFF);
    // Combine exponent and mantissa bits
    const uint32_t nonsign       = exp_bits + mantissa_bits;

    // Return combined sign bit and half-precision; handle special cases like NaN and ±inf
    return (sign >> 16) | (shl1_f > UINT32_C(0xFF000000) ? UINT16_C(0x7E00) : nonsign);
}

/*
 * Convert a 16-bit floating-point number in IEEE half-precision format to a 32-bit floating-point
 * number in IEEE single-precision format.
 */
float decode_float16(uint16_t bits) {
    // Extend the half-precision number to 32 bits and shift to the upper part of the 32-bit word
    const uint32_t f      = (uint32_t) bits << 16;
    // Extract the sign of the input number
    const uint32_t sign   = f & UINT32_C(0x80000000);
    // Shift left by one bit (equivalent to multiplying by 2)
    const uint32_t shl1_f = f + f;

    // Constants for exponent adjustment and scaling
    const uint32_t exp_offset       = UINT32_C(0xE0) << 23;
    const float    exp_scale        = decode_float(UINT32_C(0x7800000));
    // Convert normalized half-precision number to single-precision
    const float    normalized_value = decode_float((shl1_f >> 4) + exp_offset) * exp_scale;

    // Constants for handling denormalized numbers and zeros
    const uint32_t magic_mask         = UINT32_C(126) << 23;
    const float    magic_bias         = 0.5f;
    // Convert denormalized half-precision number to single-precision
    const float    denormalized_value = decode_float((shl1_f >> 17) | magic_mask) - magic_bias;

    // Determine if the input is denormalized or zero
    const uint32_t denormalized_cutoff = UINT32_C(1) << 27;
    // Combine the result of conversion with the sign of the input number
    const uint32_t result              = sign
                            | (shl1_f < denormalized_cutoff ? encode_float(denormalized_value)
                                                            : encode_float(normalized_value));
    return decode_float(result);
}

// Function to print the binary representation of a 32-bit number
void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    float value = PI;

    uint32_t ef32 = encode_float(value);
    printf("PI (float): %.8f\n", value);
    printf("float32_t encoded (hex): 0x%08X\n", ef32);
    printf("float32_t encoded (binary): ");
    print_binary(ef32);
    float df32 = decode_float(ef32);
    printf("float32_t decoded (float): %.8f\n", df32);

    // Encode the float into IEEE-754 binary16 representation
    uint16_t ef16 = encode_float16(value);
    printf("float16_t encoded (hex): 0x%04X\n", ef16);
    printf("float16_t encoded (binary): ");
    print_binary(ef16);

    // Decode the IEEE-754 binary16 representation back into a float
    float df16 = decode_float16(ef16);
    printf("float16_t decoded (float): %.8f\n", df16);

    return 0;
}
