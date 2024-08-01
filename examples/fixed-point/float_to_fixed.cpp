/*
    examples/float_to_fixed.cpp
*/
#include <iostream>

#include "fixed_point.h"

int main() {
    std::cout.precision(10);

    fixed16_t epsilon = INT_TO_FIXED(1) >> FIXED_SIZE; // calculate epsilon

    float     f = 5.7;
    fixed16_t n = FLOAT_TO_FIXED(f);

    std::cout << "epsilon: " << FIXED_TO_FLOAT(epsilon) << std::endl;
    std::cout << "float: " << f << std::endl;
    std::cout << "FLOAT_TO_FIXED: " << n << std::endl;
    std::cout << "FIXED_TO_FLOAT: " << FIXED_TO_FLOAT(n) << std::endl;

    return 0;
}
