/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/fixed-point/fixed_arithmetic.cpp
 */

#include "fixed_point.h"

#include <iostream>

int main() {
    std::cout.precision(10);

    // Define two fixed-point numbers
    fixed16_t a = FLOAT_TO_FIXED(2.5);
    fixed16_t b = FLOAT_TO_FIXED(1.3);

    // Perform arithmetic operations
    // addition and subtraction operate as expected
    fixed16_t sum        = a + b;
    fixed16_t difference = a - b;
    // multiplication and division need to be handled uniquely
    // the issue seems due to the way shifting is handled
    fixed16_t product    = a * b; // this (approximately) produces ~2^14
    fixed16_t quotient   = a / b; // this produces epsilon

    std::cout << "a: " << FIXED_TO_FLOAT(a) << std::endl;
    std::cout << "b: " << FIXED_TO_FLOAT(b) << std::endl;
    std::cout << "a + b: " << FIXED_TO_FLOAT(sum) << std::endl;
    std::cout << "a - b: " << FIXED_TO_FLOAT(difference) << std::endl;
    std::cout << "a * b: " << FIXED_TO_FLOAT(product) << std::endl;
    std::cout << "a / b: " << FIXED_TO_FLOAT(quotient) << std::endl;

    return 0;
}
