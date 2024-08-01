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
void print_binary(uint32_t bits, size_t width) {
    for (int i = width - 1; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
        if (0 == i % 4 && 0 != i) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_bit_representation(uint32_t bits) {
    printf("%f -> ", decode_float32(bits));

    // Extract the sign bit (1 bit)
    uint32_t sign = (bits >> 31) & 0x1;
    printf("%d ", sign);

    // Extract the exponent bits (8 bits)
    uint32_t exponent = (bits >> 23) & 0xFF;
    for (int i = 7; i >= 0; i--) {
        printf("%d", (exponent >> i) & 0x1);
        if (i == 4) {
            printf(" ");
        }
    }
    printf(" ");

    // Extract the mantissa bits (23 bits)
    uint32_t mantissa = bits & 0x7FFFFF;
    for (int i = 22; i >= 0; i--) {
        printf("%d", (mantissa >> i) & 0x1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_metadata(float value, const size_t bit_width) {
    // Encode the float into IEEE-754 binary32 representation
    uint32_t encoded = encode_float32(value);
    printf("value (float): %f\n", value);
    printf("encoded (hex): 0x%08X\n", encoded);
    printf("encoded (binary): ");
    print_binary(encoded, bit_width);

    // Decode the IEEE-754 binary32 representation back into a float
    float decoded = decode_float32(encoded);
    printf("decoded (float): %f\n", decoded);

    // literal internal representation
    printf("literal representation: ");
    print_bit_representation(encoded);
}

int main() {
    float        value     = 1.0f;
    const size_t bit_width = 32;

    // Sample a small range of numbers
    for (size_t step = 1; step < 5; step++) {
        print_metadata(value, bit_width);
        value += (float) step;
        puts("---");
    }

    // negative number
    print_metadata(-1.0f, bit_width);
    puts("---");

    // irrational number
    print_metadata(PI, bit_width);
    puts("---");

    // repeating fraction
    print_metadata(REPEAT, bit_width);

    return 0;
}
