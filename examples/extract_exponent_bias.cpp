/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/extract_ieee_754.cpp
 */

#include <cstdint>
#include <iostream>

// we only need to operate with powers of 2 in most cases
int32_t int32_pow2(int32_t exponent) {
    if (0 > exponent) {
        return exponent >> 1;
    }
    return 1 << exponent;
}

uint32_t uint32_pow(uint32_t base, uint32_t exponent) {
    uint32_t result = 1;
    while (exponent > 0) {
        if (exponent & 1) {
            result *= base;
        }
        base      *= base;
        exponent >>= 1;
    }
    return result;
}

uint32_t calculate_bias(uint32_t width) {
    return uint32_pow(2, width - 1) - 1;
}

int32_t convert_exponent(uint32_t bits, uint32_t width_src, uint32_t width_dest) {
    uint32_t bias_src      = calculate_bias(width_src);
    uint32_t bias_dest     = calculate_bias(width_dest);
    uint32_t exponent_mask = (1 << width_src) - 1;
    int32_t  exponent      = ((bits >> (32 - width_src)) & exponent_mask) - bias_src;
    return exponent + bias_dest;
}

int main(void) {
    // do a stress test
    for (size_t i = -7; i < 8; i++) {
        std::cout << "2^" << i << " = " << int32_pow2(i) << std::endl;
    }

    return 0;
}
