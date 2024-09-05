#ifndef QUANT_H
#define QUANT_H

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include "floating_point.h"

#include <stdint.h>

// Quantization structure
typedef struct {
    float_flex_t delta;  // Change in precision
    size_t       size;   // Number of quantized values (default to 32)
    uint8_t*     quants; // Dynamically allocated array for quantized values
    data_type_t  type;   // Data type used during quantization
} quant_t;

quant_t* encode_quant(float value, size_t size, data_type_t dtype, float_flex_t* vflex);
float    decode_quant(const quant_t* quant);

quant_t* malloc_quant(float_flex_t delta, size_t size, data_type_t dtype, uint8_t* quants);
void     free_quant(quant_t* quant);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // QUANT_H
