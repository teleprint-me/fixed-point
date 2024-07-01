#ifndef PRECISION_H
#define PRECISION_H

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

// Enumeration of data types
typedef enum {
    TYPE_FLOAT_F32,  // ieee-754 32-bit precision
    TYPE_FLOAT_F16,  // ieee-754 16-bit precision
    TYPE_FLOAT_BF16, // google brain precision
    TYPE_FLOAT_F8,   // extended 8-bit precision
    TYPE_QUANT_K8,   // k-bit precision
    TYPE_QUANT_K4,   // k-bit precision
    TYPE_MAX_COUNT,  // number of data types
} data_t;

// Data types for different precisions
typedef uint32_t float32_t;
typedef uint16_t float16_t;
typedef uint16_t bfloat16_t;
typedef uint8_t  float8_t;

typedef struct {
    float inf;  // upper bound (± ∞)
    float zero; // lower bound (typically ± 0)

    uint32_t p; // precision (number of significand digits)

    uint32_t sign;     // sign bit count
    uint32_t exponent; // exponent bit count
    uint32_t mantissa; // significand bit count

    int32_t e_bias; // bias for the exponent
    int32_t e_max;  // maximum exponent value (derived from e and e_bias)
    int32_t e_min;  // minimum exponent value (derived from e and e_bias)
} precision_t;

// Map float to internal integer representation
typedef union {
    float32_t bits;
    float     value;
} float_data_t;

// Generalized float structure
typedef struct {
    union {
        float32_t  f32;
        float16_t  f16;
        bfloat16_t bf16;
        float8_t   f8;
    } value;

    data_t type;
} float_flex_t;

// Function declarations
precision_t encode_precision(float inf, float zero, uint32_t p, uint32_t s, uint32_t e, uint32_t m);
float       decode_precision(precision_t p);

uint32_t encode_data(float value);
float    decode_data(uint32_t bits);

float_flex_t encode_float(float value, data_t type);
float        decode_float(float_flex_t flex);

// Standard 32-bit floating-point
float_flex_t encode_float32(float value);
float        decode_float32(float_flex_t flex);

// Standard 16-bit floating-point
float_flex_t encode_float16(float value);
float        decode_float16(float_flex_t flex);

// Extended 8-bit float
float_flex_t encode_float8(float value);
float        decode_float8(float_flex_t flex);

// Google brain 16-bit float
float_flex_t encode_bfloat16(float value);
float        decode_bfloat16(float_flex_t flex);

#endif // PRECISION_H
