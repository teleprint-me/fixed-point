// Original Reference: https://ieeexplore.ieee.org/document/8766229
// Original Source: /usr/include/c10/util/half.h
// 3rd Party Tutorial: https://www.geeksforgeeks.org/ieee-standard-754-floating-point-numbers/
// 3rd Party Source: https://github.com/Maratyszcza/FP16
#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI 3.141592653589793f

// 32-bit floating point (standard float)
typedef union {
    uint32_t bits;
    float    value;
} float32_t;

// Standard half-precision (IEEE 754)
typedef uint16_t float16_t;

uint32_t encode_float(float value);
float    decode_float(uint32_t b);

float16_t encode_float16(float value);

// float     decode_float16(float16_t b);

// Function to encode a float into its IEEE-754 binary32 representation
uint32_t encode_float(float value) {
    float32_t f32;
    f32.value = value;
    return f32.bits;
}

// Function to decode an IEEE-754 binary32 representation into a float
float decode_float(uint32_t b) {
    float32_t f32;
    f32.bits = b;
    return f32.value;
}

/*
 * Convert a 32-bit floating-point number in IEEE single-precision format to a 16-bit floating-point
 * number in IEEE half-precision format, in bit representation.
 *
 * @note The implementation relies on IEEE-like (no assumption about rounding mode and no operations
 * on denormals) floating-point operations and bitcasts between integer and floating-point
 * variables.
 */
uint16_t encode_float16(float value) {
    // use a uint32_t bit representation of the float values

    // set the upper bound
    const float scale_to_inf  = decode_float(UINT32_C(0x77800000));
    // set the lower bound
    const float scale_to_zero = decode_float(UINT32_C(0x08800000));

    // get the absolute value of input, scale, and push towards inf
    const float saturated_f = fabsf(value) * scale_to_inf;
    // scale down to half precision range
    float       base        = saturated_f * scale_to_zero;

    // set the 32-bit representation of the input as f
    const uint32_t f      = encode_float(value);
    // shift f left by one bit (multiplied by 2)
    const uint32_t shl1_f = f + f; // wondering if f << 1 is equivalent...
    // extract the sign bit
    const uint32_t sign   = f & UINT32_C(0x80000000);
    // extract the exponent bits
    uint32_t       bias   = shl1_f & UINT32_C(0xFF000000);
    // adjust for subnormal numbers
    if (bias < UINT32_C(0x71000000)) {
        bias = UINT32_C(0x71000000);
    }

    // adjust the base using the bias and convert back to float;
    // seems to be the inverse operation of shl1_f for float16...
    base                         = decode_float((bias >> 1) + UINT32_C(0x07800000)) + base;
    // 32-bit integer representation of the adjusted base
    const uint32_t bits          = encode_float(base);
    // extract bits for float16 (half-precision)
    const uint32_t exp_bits      = (bits >> 13) & UINT32_C(0x00007C00);
    const uint32_t mantissa_bits = bits & UINT32_C(0x00000FFF);
    // combine exponent and mantissa
    const uint32_t nonsign       = exp_bits + mantissa_bits;
    // return combined sign bit and half-precision; handle special cases like NaN and ±inf
    return (sign >> 16) | (shl1_f > UINT32_C(0xFF000000) ? UINT16_C(0x7E00) : nonsign);
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

    // Encode the float into IEEE-754 binary32 representation
    uint32_t f16 = encode_float16(value);
    printf("Encoded (hex): 0x%08X\n", f16);
    printf("Encoded (binary): ");
    print_binary(f16);

    // Decode the IEEE-754 binary32 representation back into a float
    // float decoded = decode_float16(encoded);
    // printf("Decoded (float): %.8f\n", decoded);

    return 0;
}
