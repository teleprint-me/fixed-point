// Original paper: https://ieeexplore.ieee.org/document/8766229
// Original source: /usr/include/c10/util/half.h
// 3rd party source: https://github.com/Maratyszcza/FP16
// 3rd party tutorial: https://geeksforgeeks.org/ieee-standard-754-floating-point-numbers/
#include <math.h>
#include <stdint.h>

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
    const float scale_to_inf  = decode_float(UINT32_C(0x77800000)); // Upper bound
    const float scale_to_zero = decode_float(UINT32_C(0x08800000)); // Lower bound

    const float saturated_f = fabsf(value) * scale_to_inf;
    float       base        = saturated_f * scale_to_zero;

    const uint32_t f      = encode_float(value);
    const uint32_t shl1_f = f + f;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    uint32_t       bias   = shl1_f & UINT32_C(0xFF000000);
    if (bias < UINT32_C(0x71000000)) {
        bias = UINT32_C(0x71000000);
    }

    base                         = decode_float((bias >> 1) + UINT32_C(0x07800000)) + base;
    const uint32_t bits          = encode_float(base);
    const uint32_t exp_bits      = (bits >> 13) & UINT32_C(0x00007C00);
    const uint32_t mantissa_bits = bits & UINT32_C(0x00000FFF);
    const uint32_t nonsign       = exp_bits + mantissa_bits;

    return (sign >> 16) | (shl1_f > UINT32_C(0xFF000000) ? UINT16_C(0x7E00) : nonsign);
}

/*
 * Convert a 16-bit floating-point number in IEEE half-precision format to a 32-bit floating-point
 * number in IEEE single-precision format.
 */
float decode_float16(uint16_t bits) {
    const uint32_t f      = (uint32_t) bits << 16;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    const uint32_t shl1_f = f + f;

    const uint32_t exp_offset       = UINT32_C(0xE0) << 23;
    const float    exp_scale        = decode_float(UINT32_C(0x7800000));
    const float    normalized_value = decode_float((shl1_f >> 4) + exp_offset) * exp_scale;

    const uint32_t magic_mask         = UINT32_C(126) << 23;
    const float    magic_bias         = 0.5f;
    const float    denormalized_value = decode_float((shl1_f >> 17) | magic_mask) - magic_bias;

    const uint32_t denormalized_cutoff = UINT32_C(1) << 27;
    const uint32_t result              = sign
                            | (shl1_f < denormalized_cutoff ? encode_float(denormalized_value)
                                                            : encode_float(normalized_value));
    return decode_float(result);
}
