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
    // float value = PI;
    float value = REPEAT;

    // Encode the float into IEEE-754 binary32 representation
    uint32_t encoded = encode_float(value);
    printf("value (float): %f\n", value);
    printf("encoded (hex): 0x%08X\n", encoded);
    printf("encoded (binary): ");
    print_binary(encoded);

    // Decode the IEEE-754 binary32 representation back into a float
    float decoded = decode_float(encoded);
    printf("decoded (float): %f\n", decoded);

    return 0;
}
