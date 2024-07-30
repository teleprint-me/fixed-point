// Original paper: https://ieeexplore.ieee.org/document/8766229
// Original source: /usr/include/c10/util/half.h
// 3rd party source: https://github.com/Maratyszcza/FP16
// 3rd party tutorial: https://geeksforgeeks.org/ieee-standard-754-floating-point-numbers/
#include "../include/precision.h"

#include <stdint.h>

bool float_is_close(float a, float b, float tolerance /*= FLOAT_TOLERANCE*/) {
    return fabsf(a - b) <= fmaxf(tolerance * fmaxf(fabsf(a), fabsf(b)), tolerance);
}

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
    const float_flex_t flex;

    const float scale_to_inf  = decode_data(UINT32_C(0x77800000)); // Upper bound
    const float scale_to_zero = decode_data(UINT32_C(0x08800000)); // Lower bound

    const float saturated_f = fabsf(value) * scale_to_inf;
    float       base        = saturated_f * scale_to_zero;

    const uint32_t f      = encode_data(value);
    const uint32_t shl1_f = f + f;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    uint32_t       bias   = shl1_f & UINT32_C(0xFF000000);
    if (bias < UINT32_C(0x71000000)) {
        bias = UINT32_C(0x71000000);
    }

    base                         = decode_data((bias >> 1) + UINT32_C(0x07800000)) + base;
    const uint32_t bits          = encode_data(base);
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
// float_flex_t encode_float(float value, data_t type) {
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
// float decode_float(float_flex_t encoded) {
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
