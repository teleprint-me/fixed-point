/*
    fixed-point/include/fixed_point.h
*/
#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <cstdint>

// Define constants for Lookup Table (LUT) and Fixed-Point Arithmetic
#define LUT_MAX_SIZE 1000      // Maximum allowable size of the LUT
#define EXP_MAX 10             // Maximum value for exponential calculation
#define EXP_MIN -10            // Minimum value for exponential calculation
#define LUT_SCALE 100          // Scaling factor for values stored in the LUT
#define FIXED_POINT_SCALE 10000 // Scaling factor for fixed-point arithmetic
#define FIXED_SIZE 16           // Number of fractional bits for fixed-point
#define FIXED_VAL (1 << FIXED_SIZE) // 2^16, for scaling between int and fixed-point

// Define fixed-point data type and conversion macros
typedef int32_t fixed16; // Using 32-bit integer for fixed-point calculations

// Converts a fixed-point number to an integer (truncating the fractional part)
#define FIXED_TO_INT(x) ((x) >> FIXED_SIZE)

// Converts an integer to a fixed-point number
#define INT_TO_FIXED(x) ((x) << FIXED_SIZE)

// Converts a floating-point number to fixed-point format (avoid on integer-only CPUs)
#define FLOAT_TO_FIXED(x) ((fixed16)((x) * FIXED_VAL))

// Converts a fixed-point number to floating-point format (avoid on integer-only CPUs)
#define FIXED_TO_FLOAT(x) ((float)(x) / FIXED_VAL)

#endif // FIXED_POINT_H
