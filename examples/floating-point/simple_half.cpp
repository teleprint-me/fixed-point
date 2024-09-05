/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/floating-point/simple_half.cpp
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.141592653589793f

// Standard half-precision (IEEE 754)
typedef uint32_t float32_t;
typedef uint16_t float16_t;

// 32-bit floating point (standard float)
typedef union {
    float32_t bits;
    float     value;
} float_repr_t;

float32_t encode_float32(float value);
float     decode_float32(float32_t bits);

float16_t encode_float16(float value);
float     decode_float16(float16_t bits);

// Function to encode a float into its IEEE-754 binary32 representation
float32_t encode_float32(float value) {
    float_repr_t f;
    f.value = value;
    return f.bits;
}

// Function to decode an IEEE-754 binary32 representation into a float
float decode_float32(float32_t bits) {
    float_repr_t f;
    f.bits = bits;
    return f.value;
}

// Function to encode a float into its IEEE-754 binary16 representation
float16_t encode_float16(float value) {
    // convert the float to int representation
    uint32_t bits32 = encode_float32(value);

    // calculate the bias

    // 2^(exponent - bias)
    // exponent = n = 8
    // 2^(exponent - bias) = (2 ^ (8 - 127)) - 1 - 127 = 128
    // ---
    // 2^7-127 = 1

    // 32-bit exponent bias = (2 ^ (n - 1)) - 1 = (2 ^ (8 - 1)) - 1 = 127
    uint32_t bias32 = pow(2, (8 - 1)) - 1;
    // 16-bit exponent bias = (2 ^ (n - 1)) - 1 = (2 ^ (5 - 1)) - 1 = 15
    uint16_t bias16 = pow(2, (5 - 1)) - 1;

    // extract the sign, exp, and man from the 32-bit representation

    // the sign bit becomes the most significant bit
    uint32_t sign = (bits32 & 0x80000000) >> 16;

    int32_t  exp      = ((bits32 & 0x7F800000) >> 23) - bias32 + bias16;
    uint32_t mantissa = bits32 & 0x007FFFFF;

    if (exp <= 0) {
        if (exp < -10) {
            return (float16_t) sign; // too small, become zero
        }
        // 0x00800000 -> 0 0000 0001 000 0000 0000 0000 0000 0000
        mantissa = (mantissa | 0x00800000) >> (1 - exp);
        return (float16_t) (sign | (mantissa >> 13));
    } else if (exp == 0xFF - (bias32 - bias16)) {
        if (mantissa == 0) {
            return (float16_t) (sign | 0x7C00); // infinity
        } else {
            mantissa >>= 13;
            return (float16_t) (sign | 0x7C00 | mantissa | (mantissa == 0)); // NaN
        }
    } else if (exp > 30) {
        return (float16_t) (sign | 0x7C00); // too large, become infinity
    }

    return (float16_t) (sign | (exp << 10) | (mantissa >> 13));
}

float decode_float16(float16_t value) {
    uint32_t sign     = (value & 0x8000) << 16;
    int32_t  exp      = (value & 0x7C00) >> 10;
    uint32_t mantissa = (value & 0x03FF) << 13;

    if (exp == 0) {
        if (mantissa == 0) {
            return decode_float32(sign); // zero
        }
        exp = 1;
        while (!(mantissa & 0x00800000)) {
            mantissa <<= 1;
            exp       -= 1;
        }
        mantissa &= 0x007FFFFF;
    } else if (exp == 0x1F) {
        if (mantissa == 0) {
            return decode_float32(sign | 0x7F800000); // infinity
        } else {
            return decode_float32(sign | 0x7F800000 | mantissa); // NaN
        }
    } else {
        exp += 127 - 15;
    }

    uint32_t result = sign | (exp << 23) | mantissa;
    return decode_float32(result);
}

int main() {
    // Anything above 1.0e-4f produces garbage output because of the limited precision
    // This actually makes sense because the ranges are between 5 and -4 inclusive
    // This would be an accurate representation of a 16-bit value.
    // In range values produce garbage outputs when converted back to 32-bit
    // Out of range values seem to be zeroed out.
    float test_values[] = {
        0.0f,
        1.0f,
        -1.0f,
        PI,
        65504.0f,
        1.0e-4f,
        1.23456789f,
        INFINITY,
        -INFINITY,
        NAN,
        // Additional test cases outside of the range for half-precision format
        // 1.0e+38f should probably return inf or the highest value within range
        1.0e+38f, // retuns inf (overflow)
        // 1.0e-40f should probably return -inf or the lowest value
        1.0e-40f,                   // zeroed out (underflow)
                                    // within range)
        (float) (1 << 31) + 1.0f,   // returns -inf (overflow)
        1.2f * (1 << 4),            // surprisingly accurate  (precision loss)
        (float) (1LL << 63),        // returns -inf (overflow)
        -(float) (1LL << 63),       // returns inf (overflow)
        (float) -((1LL << 58) | 1), // returns -inf (overflow)
    };

    size_t num_values = sizeof(test_values) / sizeof(test_values[0]);

    for (size_t i = 0; i < num_values; ++i) {
        float     value   = test_values[i];
        float16_t encoded = encode_float16(value);
        float     decoded = decode_float16(encoded);

        printf("Original: %f, Encoded: 0x%04X, Decoded: %f\n", value, encoded, decoded);
    }

    return 0;
}
