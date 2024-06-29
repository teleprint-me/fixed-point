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

// Map float to internal integer representation
typedef union {
    uint32_t bits;
    float    value;
} float_data_t;

// Data types for different precisions
typedef uint32_t float32_t;
typedef uint16_t float16_t;
typedef uint16_t bfloat16_t;
typedef uint8_t  float8_t;

// Generalized float structure
typedef struct {
    union {
        float32_t  f32;
        float16_t  f16;
        bfloat16_t bf16;
        float8_t   f8;
    } value;

    data_t type;
} flex_float_t;

// Quantization structure
typedef struct {
    flex_float_t delta;  // Change in precision
    size_t       size;   // Number of quantized values (default to 32)
    uint8_t*     quants; // Dynamically allocated array for quantized values
    data_t       type;   // Data type used during quantization
} quant_t;

// Function to encode a float value into a specified type
flex_float_t encode_float(float value, data_t type);

// Function to decode a flex_float_t value back to float
float decode_float(flex_float_t value);

// Function to encode a series of float values into quantized form
quant_t* encode_quant(float value, size_t size, data_t dtype, flex_float_t* vector);

// Function to decode a quantized value back to float
float decode_quant(const quant_t* quant);

// Function to allocate memory for a quant_t structure
quant_t* malloc_quant(flex_float_t delta, size_t size, data_t dtype, uint8_t* quants);

// Function to free memory of a quant_t structure
void free_quant(quant_t* quant);

#endif // PRECISION_H
