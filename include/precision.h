#ifndef PRECISION_H
#define PRECISION_H

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef enum DataType {
    TYPE_FLOAT_F32,  // ieee-754
    TYPE_FLOAT_F16,  // ieee-754
    TYPE_FLOAT_BF16, // google brain
    TYPE_FLOAT_F8,   // custom 8-bit precision
    TYPE_QUANT_K8,   // k-bit precision
    TYPE_QUANT_K4,   // k-bit precision
    TYPE_MAX_COUNT,  // number of data types
} data_t;

// Generalized float structure
typedef struct {
    union {
        uint32_t f32;
        uint16_t f16;
        uint8_t  f8;
    } bits;

    float  value;
    data_t type;
} float_t;

// Quantization structure
typedef struct {
    float_t  delta;  // Change in precision
    size_t   size;   // Number of quantized values (default to 32)
    uint8_t* quants; // Dynamically allocated array for quantized values
    data_t   type;   // Data type used during quantization
} quant_t;

// Function declarations
float_t encode_float(float value, data_t type);
float   decode_float(float_t value);

quant_t* encode_quant(float value, size_t size, data_t dtype);
float    decode_quant(const quant_t* quant);

quant_t* malloc_quant(float_t delta, size_t size, data_t dtype, uint8_t* quants);
void     free_quant(quant_t* quant);

#endif // PRECISION_H
