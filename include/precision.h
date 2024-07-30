#ifndef PRECISION_H
#define PRECISION_H

#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

// Enumeration of data types
typedef enum {
    TYPE_FLOAT_F32,  // IEEE-754 32-bit precision
    TYPE_FLOAT_F16,  // IEEE-754 16-bit precision
    TYPE_FLOAT_BF16, // Google Brain bfloat16 precision
    TYPE_FLOAT_F8,   // Extended 8-bit precision
    TYPE_QUANT_K8,   // k-bit precision
    TYPE_QUANT_K4,   // k-bit precision
    TYPE_MAX_COUNT,  // Number of data types
} data_t;

// Data types for different precisions
typedef uint32_t float32_t;
typedef uint16_t float16_t;
typedef uint16_t bfloat16_t;
typedef uint8_t  float8_t;

// Struct to define precision parameters
typedef struct {
    float inf;  // Upper bound (± ∞)
    float zero; // Lower bound (typically ± 0)

    uint32_t p;        // Precision (number of significand digits)
    uint32_t sign;     // Sign bit count
    uint32_t exponent; // Exponent bit count
    uint32_t mantissa; // Significand bit count

    int32_t e_bias; // Bias for the exponent
    int32_t e_max;  // Maximum exponent value (derived from e and e_bias)
    int32_t e_min;  // Minimum exponent value (derived from e and e_bias)
} precision_t;

// Union to map float to internal integer representation
typedef union {
    float32_t bits;
    float     value;
} float_data_t;

// Generalized float structure for various float types
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

// Encode float value based on type
float_flex_t encode_float(float value, data_t type);
float        decode_float(const float_flex_t* flex);

// Encode standard 32-bit floating-point
float32_t encode_float32(float value);
float     decode_float32(const float32_t* flex);

// Encode standard 16-bit floating-point
float16_t encode_float16(float value);
float     decode_float16(const float16_t* flex);

// Encode extended 8-bit float
float8_t encode_float8(float value);
float    decode_float8(const float8_t* flex);

// Encode Google Brain 16-bit float
bfloat16_t encode_bfloat16(float value);
float      decode_bfloat16(const bfloat16_t* flex);

#endif // PRECISION_H
