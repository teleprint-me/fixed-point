#include <stdint.h>

// 32-bit floating point (standard float)
typedef union {
    uint32_t bits;
    float    value;
} float32_t;

typedef uint16_t bfloat16_t;

/**
 * Converts float32 to bfloat16.
 */
bfloat16_t float_to_bfloat16(float value) {
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
float bfloat16_to_float(bfloat16_t bf16) {
    float32_t f32;
    f32.bits = (uint32_t) bf16 << 16;
    return f32.value;
}
