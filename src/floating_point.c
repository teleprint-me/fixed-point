/**
 * Copyright © 2024 Austin Berrio
 *
 * @file src/floating_point.c
 *
 * @brief A simple and easy-to-use API in C for handling various floating-point
 *        precisions, including 32-bit (float), 16-bit (half precision float:
 *        IEEE-754 & bfloat16), 16-bit Google Brain format, and extended 8-bit
 *        floats.
 *
 * Only pure C is used with minimal dependencies on external libraries.
 *
 * @note Official document
 * @ref https://ieeexplore.ieee.org/document/8766229
 *
 * @note 3rd party work
 * @ref shttps://geeksforgeeks.org/ieee-standard-754-floating-point-numbers/
 *
 * @note Source code
 * @ref /usr/include/c10/util/half.h
 * @ref https://github.com/Maratyszcza/FP16
 * @ref https://github.com/pytorch/pytorch/blob/main/c10/util/Half.h
 */

#include "floating_point.h"

#include <stdint.h>
#include <stdio.h>

/*
 * Binary 32-bit floating point encoding
 */
float32_t encode_float32(float value) {
    float_data_t data;
    data.value = value;
    return data.bits;
}

/*
 * Binary 32-bit floating point decoding
 */
float decode_float32(float32_t bits) {
    float_data_t data;
    data.bits = bits;
    return data.value;
}

/*
 * Binary 16-bit floating point representation
 */
float16_t encode_float16(float value) {
    // const float_flex_t flex;

    const float scale_to_inf  = decode_float32(UINT32_C(0x77800000)); // Upper bound
    const float scale_to_zero = decode_float32(UINT32_C(0x08800000)); // Lower bound

    const float saturated_f = fabsf(value) * scale_to_inf;
    float       base        = saturated_f * scale_to_zero;

    const uint32_t f      = encode_float32(value);
    const uint32_t shl1_f = f + f;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    uint32_t       bias   = shl1_f & UINT32_C(0xFF000000);
    if (bias < UINT32_C(0x71000000)) {
        bias = UINT32_C(0x71000000);
    }

    base                         = decode_float32((bias >> 1) + UINT32_C(0x07800000)) + base;
    const uint32_t bits          = encode_float32(base);
    const uint32_t exp_bits      = (bits >> 13) & UINT32_C(0x00007C00);
    const uint32_t mantissa_bits = bits & UINT32_C(0x00000FFF);
    const uint32_t nonsign       = exp_bits + mantissa_bits;

    return (sign >> 16) | (shl1_f > UINT32_C(0xFF000000) ? UINT16_C(0x7E00) : nonsign);
}

float decode_float16(float16_t bits) {
    const uint32_t f      = (uint32_t) bits << 16;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    const uint32_t shl1_f = f + f;

    const uint32_t exp_offset       = UINT32_C(0xE0) << 23;
    const float    exp_scale        = decode_float32(UINT32_C(0x7800000));
    const float    normalized_value = decode_float32((shl1_f >> 4) + exp_offset) * exp_scale;

    const uint32_t magic_mask         = UINT32_C(126) << 23;
    const float    magic_bias         = 0.5f;
    const float    denormalized_value = decode_float32((shl1_f >> 17) | magic_mask) - magic_bias;

    const uint32_t denormalized_cutoff = UINT32_C(1) << 27;
    const uint32_t result              = sign
                            | (shl1_f < denormalized_cutoff ? encode_float32(denormalized_value)
                                                            : encode_float32(normalized_value));
    return decode_float32(result);
}

/*
 * 16-bit brain floating point representation
 */
bfloat16_t encode_bfloat16(float value) {
    // Take the higher 16 bits of the float32 representation
    uint32_t bits = encode_float32(value);

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
    float_data_t data;
    data.bits = (uint32_t) bf16 << 16;
    return data.value;
}

// Helper function to encode a float based on its data type
// float_flex_t encode_float32(float value, data_t type) {
//     float_flex_t encoded;
//     encoded.type      = type;
//     encoded.value.f32 = value;
//     switch (type) {
//         case TYPE_FLOAT_F32:
//             encoded.bits.f32 = (uint32_t) value;
//             break;
//         case TYPE_FLOAT_F16:
//             // Encoding logic for float16
//             // Placeholder: real implementation needed
//             encoded.bits.f16 = (uint16_t) value;
//             break;
//         case TYPE_FLOAT_F8:
//             // Encoding logic for float8
//             // Placeholder: real implementation needed
//             encoded.bits.f8 = (uint8_t) value;
//             break;
//         default:
//             // Unsupported type
//             assert(0);
//     }
//     return encoded;
// }

// Helper function to decode a float based on its data type
// float decode_float32(float_flex_t encoded) {
//     float value = 0.0f;
//     switch (encoded.type) {
//         case TYPE_FLOAT_F32:
//             value = *(float*) &encoded.bits.f32;
//             break;
//         case TYPE_FLOAT_F16:
//             // Decoding logic for float16
//             // Placeholder: real implementation needed
//             value = (float) encoded.bits.f16;
//             break;
//         case TYPE_FLOAT_F8:
//             // Decoding logic for float8
//             // Placeholder: real implementation needed
//             value = (float) encoded.bits.f8;
//             break;
//         default:
//             // Unsupported type
//             assert(0);
//     }
//     return value;
// }

// Function to print the binary representation of a 32-bit number
void print_32bit_raw(float32_t bits, size_t bit_width) {
    for (int i = bit_width - 1; i >= 0; i--) {
        printf("%d", (bits >> i) & 1);
        if (0 == i % 4 && 0 != i) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_32bit_formatted(float32_t bits) {
    printf("%f -> ", decode_float32(bits));

    // Extract the sign bit (1 bit)
    uint32_t sign = (bits >> 31) & 0x1;
    printf("%d ", sign);

    // Extract the exponent bits (8 bits)
    uint32_t exponent = (bits >> 23) & 0xFF;
    for (int i = 7; i >= 0; i--) {
        printf("%d", (exponent >> i) & 0x1);
        if (i == 4) {
            printf(" ");
        }
    }
    printf(" ");

    // Extract the mantissa bits (23 bits)
    uint32_t mantissa = bits & 0x7FFFFF;
    for (int i = 22; i >= 0; i--) {
        printf("%d", (mantissa >> i) & 0x1);
        if (i % 4 == 0) {
            printf(" ");
        }
    }
    printf("\n");
}

void print_32bit_metadata(float value, const size_t bit_width) {
    // Encode the float into IEEE-754 binary32 representation
    uint32_t encoded = encode_float32(value);
    printf("value (float): %f\n", value);
    printf("encoded (hex): 0x%08X\n", encoded);
    printf("encoded (binary): ");
    print_32bit_raw(encoded, bit_width);

    // Decode the IEEE-754 binary32 representation back into a float
    float decoded = decode_float32(encoded);
    printf("decoded (float): %f\n", decoded);

    // literal internal representation
    printf("literal representation: ");
    print_32bit_formatted(encoded);
}
