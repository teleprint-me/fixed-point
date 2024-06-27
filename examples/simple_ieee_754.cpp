#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define PI 3.141592653589793f

typedef union {
    float f;
    uint32_t bits;
} float32_t;

// Function to encode a float into its IEEE-754 binary32 representation
uint32_t encode_float(float f) {
    float32_t u;
    u.f = f;
    return u.bits;
}

// Function to decode an IEEE-754 binary32 representation into a float
float decode_float(uint32_t bits) {
    float32_t u;
    u.bits = bits;
    return u.f;
}

// Function to print the binary representation of a 32-bit number
void print_binary(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    float value = PI;

    // Encode the float into IEEE-754 binary32 representation
    uint32_t encoded = encode_float(value);
    printf("Encoded (hex): 0x%08X\n", encoded);
    printf("Encoded (binary): ");
    print_binary(encoded);

    // Decode the IEEE-754 binary32 representation back into a float
    float decoded = decode_float(encoded);
    printf("Decoded (float): %f\n", decoded);

    return 0;
}
