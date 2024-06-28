#include <stdint.h>
#include <stdio.h>

#define PI 3.141592653589793f

// 32-bit floating point (standard float)
typedef union {
    uint32_t bits;
    float    value;
} float32_t;

typedef uint16_t bfloat16_t;

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

/**
 * Converts float32 to bfloat16.
 */
bfloat16_t encode_bfloat16(float value) {
    float32_t f32;
    f32.value = value;

    // Take the higher 16 bits of the float32 representation
    uint32_t bits = f32.bits;

    // Handle NaN: force to quiet NaN
    if ((bits & 0x7fffffff) > 0x7f800000) {
        return (bits >> 16) | 0x0040;
    }

    // Handle subnormals: flush to zero
    if ((bits & 0x7f800000) == 0) {
        return (bits >> 16) & 0x8000;
    }

    // Rounding: round to nearest even
    uint32_t rounding_bias = (bits & 0x0000ffff) > 0x00007fff    ? 1
                             : (bits & 0x00018000) == 0x00018000 ? 1
                                                                 : 0;
    return (bits + rounding_bias) >> 16;
}

/**
 * Converts bfloat16 to float32.
 */
float decode_bfloat16(bfloat16_t bf16) {
    float32_t f32;
    f32.bits = (uint32_t) bf16 << 16;
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
    float value = PI;

    uint32_t ef32 = encode_float(value);
    printf("PI (float): %.8f\n", value);
    printf("float32_t encoded (hex): 0x%08X\n", ef32);
    printf("float32_t encoded (binary): ");
    print_binary(ef32);
    float df32 = decode_float(ef32);
    printf("float32_t decoded (float): %.8f\n", df32);

    // Encode the float into IEEE-754 binary16 representation
    uint16_t ebf16 = encode_bfloat16(value);
    printf("bfloat16_t encoded (hex): 0x%04X\n", ebf16);
    printf("bfloat16_t encoded (binary): ");
    print_binary(ebf16);

    // Decode the IEEE-754 binary16 representation back into a float
    float dbf16 = decode_bfloat16(ebf16);
    printf("bfloat16_t decoded (float): %.8f\n", dbf16);

    return 0;
}
