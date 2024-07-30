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
} data_type_t;

// Data types for different precisions
typedef uint32_t float32_t;
typedef uint16_t float16_t;
typedef uint16_t bfloat16_t;
typedef uint8_t  float8_t;

/**
 * @brief A union representing a flexible floating-point representation,
 *        allowing access to both raw bit data and its corresponding value.
 *
 * @param bits  Raw 32-bit integer bit representation of the floating-point number.
 * @param value The actual 32-bit floating-point value represented by this data structure.
 */
typedef union {
    float32_t bits;
    float     value;
} float_data_t;

/**
 * @brief Represents a flexible floating point data structure capable of
 *        handling different precisions and formats.
 *
 * @param value  The actual floating-point value represented by this data structure.
 * @param type   Indicates the specific precision or format (e.g., float32, bfloat16)
 */
typedef struct {
    float_data_t value;
    data_type_t  type;
} float_flex_t;

/**
 * @brief Encodes a given float value into its corresponding 32-bit representation.
 *
 * @param[in] value The floating point number to be encoded.
 *
 * @return The resulting encoded 32-bit integer representation of the input value.
 */
float32_t encode_float32(float value);

/**
 * @brief Decodes a given 32-bit integer representation into its corresponding float value.
 *
 * @param[in] bits The encoded 32-bit integer bit representation of the floating-point number.
 *
 * @return The decoded actual 32-bit floating-point value represented by this data structure.
 */
float decode_float32(float32_t bits);

// Encode standard 16-bit floating-point
float16_t encode_float16(float value);
float     decode_float16(float16_t bits);

// Encode extended 8-bit float
float8_t encode_float8(float value);
float    decode_float8(float8_t bits);

// Encode Google Brain 16-bit float
bfloat16_t encode_bfloat16(float value);
float      decode_bfloat16(bfloat16_t flex);

#endif // PRECISION_H
