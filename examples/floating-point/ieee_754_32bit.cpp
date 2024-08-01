/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/simple_ieee_754.cpp
 *
 * @brief A simple example showcasing 32-bit floating-point representation
 * as a internal 32-bit as integer in literal binary format.
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI     3.141592653589793f
#define REPEAT ((124.f) + (1.f / 3.f)) // 1 / 3 = 0.333...; // 3 is repeating

// Struct to define precision parameters
typedef struct {
    float inf;  // Upper bound (± ∞)
    float zero; // Lower bound (typically ± 0)

    uint32_t p;        // Precision (number of significand digits)
    uint32_t sign;     // Sign bit count
    uint32_t exponent; // Exponent bit count
    uint32_t mantissa; // Significand bit count

    int32_t e_bias; // Bias for the exponent
    int32_t e_max;  // Maximum exponent value (derived from e and e_bias)
    int32_t e_min;  // Minimum exponent value (derived from e and e_bias)
} precision_t;

typedef union {
    uint32_t bits;
    float    value;
} float32_t;

// Function to encode a float into its IEEE-754 binary32 representation
uint32_t encode_float32(float value) {
    float32_t f32;
    f32.value = value;
    return f32.bits;
}

// Function to decode an IEEE-754 binary32 representation into a float
float decode_float32(uint32_t bits) {
    float32_t f32;
    f32.bits = bits;
    return f32.value;
}

// Function to print the binary representation of a 32-bit number
void print_binary(void* bits, size_t width) {
    uint32_t* repr = (uint32_t*) bits;

    for (int step = width - 1; step >= 0; step--) {
        printf("%d", ((*repr) >> step) & 1);

        if (0 == step % 4) {
            printf(" ");
        }
    }

    printf("\n");
}

void print_bit_representation(uint32_t bits, size_t s, size_t e, size_t m) {
    // Print the floating-point value
    printf("%f -> ", decode_float32(bits));

    // Extract the sign bit
    uint32_t sign = (bits >> (s - 1)) & 0x1;
    printf("%d ", sign);

    // Extract the exponent bits (8 bits)
    uint32_t exponent = (bits >> m) & 0xFF;
    for (int i = (e - 1); i >= 0; i--) {
        printf("%d", (exponent >> i) & 0x1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }

    // Extract the mantissa bits (23 bits)
    uint32_t mantissa = bits & 0x7FFFFF;
    for (int i = m - 1; i >= 0; i--) {
        printf("%d", (mantissa >> i) & 0x1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    // float value = PI;
    const size_t bit_width = 32; // float is 32-bits wide
    float        value     = 2;

    // Encode the float into IEEE-754 binary32 representation
    uint32_t encoded = encode_float32(value);
    printf("value (float): %f\n", value);
    printf("encoded (hex): 0x%08X\n", encoded);
    printf("encoded (binary): ");
    print_binary(&encoded, bit_width);

    // Decode the IEEE-754 binary32 representation back into a float
    float decoded = decode_float32(encoded);
    printf("decoded (float): %f\n", decoded);

    // literal internal representation
    printf("literal representation: ");
    print_bit_representation(encoded, 32, 8, 23);

    return 0;
}
