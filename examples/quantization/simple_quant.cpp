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

// Standard half-precision (IEEE 754)
typedef uint8_t quant8_t;

uint32_t encode_float(float value);
float    decode_float(uint32_t bits);

uint32_t encode_quant8(float value);
float    decode_quant8(uint32_t bits);

typedef struct {
    uint8_t sign : 1;
    uint8_t exponent : 3;
    uint8_t mantissa : 4;
} float8_t;

uint8_t encode_float8(float value) {
    uint32_t f32      = encode_float(value);
    uint8_t  sign     = (f32 >> 31) & 0x1;
    // Adjusting bias from 127 (float) to 3 (float8)
    int32_t  exponent = ((f32 >> 23) & 0xFF) - 127 + 3;
    // Keep 4 bits of mantissa
    uint32_t mantissa = (f32 >> 19) & 0xF;

    if (exponent < 0) {
        // Denormalized number or too small, set to zero
        exponent = 0;
        mantissa = 0;
    } else if (exponent > 7) {
        // Overflow, set to infinity
        exponent = 7;
        mantissa = 0;
    }

    float8_t f8;
    f8.sign     = sign;
    f8.exponent = exponent;
    f8.mantissa = mantissa;
    return *((uint8_t*) &f8);
}

float decode_float8(uint8_t bits) {
    float8_t* f8       = (float8_t*) &bits;
    uint32_t  sign     = f8->sign << 31;
    int32_t   exponent = f8->exponent - 3 + 127; // Adjusting bias from 3 (float8) to 127 (float)
    uint32_t  mantissa = f8->mantissa << 19;     // Adjust mantissa to 23 bits

    if (f8->exponent == 0) {
        // Denormalized number
        if (f8->mantissa == 0) {
            // Zero
            exponent = 0;
            mantissa = 0;
        } else {
            // Denormalized, adjust exponent
            exponent = 127 - 3 + 1;
        }
    } else if (f8->exponent == 7) {
        // Infinity or NaN
        exponent = 0xFF;
        if (f8->mantissa != 0) {
            mantissa |= 1 << 22; // NaN
        }
    }

    uint32_t f32 = sign | (exponent << 23) | mantissa;
    return decode_float(f32);
}
