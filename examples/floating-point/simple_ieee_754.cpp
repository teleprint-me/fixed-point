/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/floating-point/simple_ieee_754.cpp
 *
 * @brief A simple example showcasing 32-bit floating-point representation
 * as a internal 32-bit as integer in literal binary format.
 */

#include "floating_point.h"

#include <math.h>
#include <stdint.h>
#include <stdio.h>

#define PI     3.141592653589793f
#define REPEAT ((124.f) + (1.f / 3.f)) // 1 / 3 = 0.333...; // 3 is repeating

int main() {
    float        value     = 1.0f;
    const size_t bit_width = 32;

    // Sample a small range of numbers
    for (size_t step = 1; step < 5; step++) {
        print_32bit_metadata(value, bit_width);
        value += (float) step;
        puts("---");
    }

    // negative number
    print_32bit_metadata(-1.0f, bit_width);
    puts("---");

    // irrational number
    print_32bit_metadata(PI, bit_width);
    puts("---");

    // repeating fraction
    print_32bit_metadata(REPEAT, bit_width);

    return 0;
}
