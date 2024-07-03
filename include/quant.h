#ifndef QUANT_H
#define QUANT_H

#include "precision.h"

#include <stdint.h>

// Quantization structure
typedef struct {
    float_flex_t delta;  // Change in precision
    size_t       size;   // Number of quantized values (default to 32)
    uint8_t*     quants; // Dynamically allocated array for quantized values
    data_t       type;   // Data type used during quantization
} quant_t;

quant_t* encode_quant(float value, size_t size, data_t dtype, float_flex_t* vflex);
float    decode_quant(const quant_t* quant);

quant_t* malloc_quant(float_flex_t delta, size_t size, data_t dtype, uint8_t* quants);
void     free_quant(quant_t* quant);

#endif // QUANT_H
