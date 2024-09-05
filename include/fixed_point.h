/**
 * Copyright © 2024 Austin Berrio
 *
 * @file include/fixed_point.h
 *
 * @brief Fixed-point arithmetic library header.
 *
 * This file defines the types and macros necessary for fixed-point arithmetic
 * operations. The library provides efficient computation for systems that may
 * lack hardware floating-point support or require precise numerical computations.
 *
 * The fixed-point format is represented using 16 fractional bits, allowing for
 * a trade-off between range and precision. This header includes conversion macros
 * between integers, fixed-point numbers, and floating-point numbers.
 */

#ifndef FIXED_POINT_H
#define FIXED_POINT_H

#include <stdint.h>

/// Maximum allowable size of the Lookup Table (LUT).
#define LUT_MAX_SIZE      1000

/// Maximum exponent value for exponential calculations.
#define EXP_MAX           10

/// Minimum exponent value for exponential calculations.
#define EXP_MIN           -10

/// Scaling factor for values stored in the LUT. It defines the granularity of the LUT values.
#define LUT_SCALE         100

/// Scaling factor for fixed-point arithmetic, representing 2^16.
#define FIXED_POINT_SCALE 10000

/// Number of fractional bits in the fixed-point representation.
#define FIXED_SIZE        16

/// Fixed-point scaling factor, equivalent to 2^FIXED_SIZE (65536). Used to scale between integer
/// and fixed-point.
#define FIXED_VAL         (1 << FIXED_SIZE)

/**
 * @typedef fixed16_t
 * @brief Type definition for 16-bit fractional fixed-point numbers.
 *
 * This type is represented as a 32-bit signed integer. The lower 16 bits
 * store the fractional part, while the upper bits store the integer part.
 */
typedef int32_t fixed16_t;

/**
 * @brief Converts a fixed-point number to an integer.
 *
 * This macro truncates the fractional part of the fixed-point number.
 *
 * @param x The fixed-point number to convert.
 * @return The integer representation of the fixed-point number.
 */
#define FIXED_TO_INT(x)   ((x) >> FIXED_SIZE)

/**
 * @brief Converts an integer to a fixed-point number.
 *
 * This macro shifts the integer value to the left by the number of fractional bits.
 *
 * @param x The integer to convert.
 * @return The fixed-point representation of the integer.
 */
#define INT_TO_FIXED(x)   ((x) << FIXED_SIZE)

/**
 * @brief Converts a floating-point number to fixed-point format.
 *
 * This macro multiplies the floating-point number by FIXED_VAL to convert it
 * into the fixed-point representation. It should be avoided on integer-only CPUs
 * as it involves floating-point arithmetic.
 *
 * @param x The floating-point number to convert.
 * @return The fixed-point representation of the floating-point number.
 */
#define FLOAT_TO_FIXED(x) ((fixed16_t) ((x) * FIXED_VAL))

/**
 * @brief Converts a fixed-point number to floating-point format.
 *
 * This macro divides the fixed-point number by FIXED_VAL to convert it
 * into the floating-point representation. It should be avoided on integer-only CPUs
 * as it involves floating-point arithmetic.
 *
 * @param x The fixed-point number to convert.
 * @return The floating-point representation of the fixed-point number.
 */
#define FIXED_TO_FLOAT(x) ((float) (x) / FIXED_VAL)

#endif // FIXED_POINT_H
