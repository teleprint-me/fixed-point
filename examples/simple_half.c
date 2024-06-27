#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.141592653589793f

// 32-bit floating point (standard float)
typedef union Float32 {
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

// Function to encode a float into its IEEE-754 binary16 representation
float16_t encode_float16(float value) {
    // Convert float to 32-bit representation
    const uint32_t w        = encode_float(value);
    // Extract the sign bit and align it for 16-bit
    const uint32_t sign     = (w & 0x80000000) >> 16;
    // Extract the mantissa
    const uint32_t mantissa = w & 0x007FFFFF;
    // Extract exponent, adjust bias from 127 to 15
    const int32_t  exp      = ((w & 0x7F800000) >> 23) - 127 + 15;

    if (exp <= 0) {
        // Handle subnormal numbers and zero
        return (float16_t) (sign | (mantissa >> 13));
    } else if (exp >= 31) {
        // Handle infinity and NaN
        return (float16_t) (sign | 0x7C00 | (mantissa ? 0x200 : 0));
    } else {
        // Handle normal numbers
        return (float16_t) (sign | (exp << 10) | (mantissa >> 13));
    }
}

// Function to decode an IEEE-754 binary16 representation into a float
float decode_float16(float16_t value) {
    const uint32_t sign     = (value & 0x8000) << 16;
    const uint32_t mantissa = (value & 0x03FF) << 13;
    const int32_t  exp      = ((value & 0x7C00) >> 10) - 15 + 127;

    if (exp <= 0) {
        // Handle subnormal numbers and zero
        return decode_float(sign | mantissa);
    } else if (exp >= 255) {
        // Handle infinity and NaN
        return decode_float(sign | 0x7F800000 | mantissa);
    } else {
        // Handle normal numbers
        return decode_float(sign | (exp << 23) | mantissa);
    }
}

int main() {
    float  test_values[] = {0.0f, 1.0f, -1.0f, PI, 65504.0f, 1.0e-40f, INFINITY, -INFINITY, NAN};
    size_t num_values    = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_values; ++i) {
        float     value   = test_values[i];
        float16_t encoded = encode_float16(value);
        float     decoded = decode_float16(encoded);

        printf("Original: %f, Encoded: 0x%04X, Decoded: %f\n", value, encoded, decoded);
    }

    return 0;
}
