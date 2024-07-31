/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/extract_exponent_bias.cpp
 */

#include <cstdint>
#include <iostream>

// we only need to operate with powers of 2 in most cases
uint32_t uint32_pow2(uint32_t exponent) {
    // explicitly type cast to detect values less than 0.
    // if we do not type cast, they go undetected.
    if (0 > (int32_t) exponent) {
        std::cout << "negative exponent detected" << std::endl;
        throw std::runtime_error("Integers cannot support negative exponents");
    }
    // efficient way to multiply by a power of base 2
    return 1 << exponent; // equivalent to 2^exponent
}

uint32_t uint32_pow(uint32_t base, uint32_t exponent) {
    // explicitly type cast to detect values less than 0.
    // if we do not type cast, they go undetected.
    if (0 > (int32_t) exponent) {
        std::cout << "negative exponent detected" << std::endl;
        throw std::runtime_error("Integers cannot support negative exponents");
    }

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
    // perform regular tests
    for (size_t i = 0; i < 8; i++) {
        std::cout << "2^" << i << " = " << uint32_pow2(i) << std::endl;
    }

    // do a stress test
    for (int i = -7; i < 8; i++) {
        std::cout << "2^" << i << " = " << uint32_pow2(i) << std::endl;
    }

    return 0;
}
