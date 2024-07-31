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
void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_bit_representation(uint32_t n, size_t width) {
    // Print the floating-point value
    printf("%f -> ", decode_float32(n));

    // Extract the sign bit
    uint32_t sign = (n >> 31) & 0x1;
    printf("%d ", sign);

    // Extract the exponent bits (8 bits)
    uint32_t exponent = (n >> 23) & 0xFF;
    for (int i = 7; i >= 0; i--) {
        printf("%d", (exponent >> i) & 0x1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf(" ");

    // Extract the mantissa bits (23 bits)
    uint32_t mantissa = n & 0x7FFFFF;
    for (int i = 22; i >= 0; i--) {
        printf("%d", (mantissa >> i) & 0x1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    // float value = PI;
    float value = 10;

    // Encode the float into IEEE-754 binary32 representation
    uint32_t encoded = encode_float32(value);
    printf("value (float): %f\n", value);
    printf("encoded (hex): 0x%08X\n", encoded);
    printf("encoded (binary): ");
    print_binary(encoded);

    // Decode the IEEE-754 binary32 representation back into a float
    float decoded = decode_float32(encoded);
    printf("decoded (float): %f\n", decoded);

    // literal internal representation
    printf("literal representation: ");
    print_bit_representation(encoded, 32);

    return 0;
}
