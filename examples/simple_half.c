#include <math.h>
#include <stdint.h>

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
float     decode_float16(float16_t value);

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
    uint32_t bits = encode_float(value);

    // Extract the components of the half-precision float
    uint32_t sign        = (bits >> 15) & 0x1;
    int32_t  exponent    = ((bits >> 23) & 0xFF) - 127 + 15;
    uint32_t significand = bits & 0x7FFFFF;

    if (exponent <= 0) {
        // Subnormal number
        if (exponent < -10) {
            // Too small to be represented as half-precision
            exponent    = 0;
            significand = 0;
        } else {
            significand = (significand | 0x80000000U) >> (1 - exponent);
            exponent    = 0;
        }
    } else if (exponent >= 31) {
        // Too large to be represented as half-precision, set to infinity
        exponent    = 31;
        significand = 0;
    } else {
        // Normal number
        significand >>= 13;
    }

    // Combine sign, exponent, and significand
    return (sign << 15) | (exponent << 10) | significand;
}
