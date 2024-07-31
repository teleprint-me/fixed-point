/**
 * Copyright © 2024 Austin Berrio
 *
 * @file examples/extract_exponent_bias.cpp
 */

#include <cassert>
#include <cstdint>
#include <iostream>

// we only need to operate with powers of 2 in most cases
uint32_t uint32_pow2(uint32_t exponent) {
    // Check for negative exponent and throw an exception if detected
    if (0 > static_cast<int32_t>(exponent)) {
        throw std::invalid_argument(
            "Integers cannot support negative exponents. Use pow or an equivalent function instead."
        );
    }

    // efficient way to multiply by a power of base 2
    return 1 << exponent; // equivalent to 2^exponent
}

/**
 * @brief Computes the power of a base raised to an exponent, limited to positive exponents.
 *
 * @param base The base value, must be non-negative.
 * @param exponent The exponent value, must be non-negative.
 * @return uint32_t The result of base raised to the power of exponent.
 * @throws std::invalid_argument If the exponent is negative.
 */
uint32_t uint32_pow(uint32_t base, uint32_t exponent) {
    // Check for negative exponent and throw an exception if detected
    if (0 > static_cast<int32_t>(exponent)) {
        throw std::invalid_argument(
            "Integers cannot support negative exponents. Use pow or an equivalent function instead."
        );
    }

    // Fast exponentiation by squaring
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

int main() {
    try {
        // Test calculating integer-based exponent values
        for (size_t i = 0; i < 8; i++) {
            std::cout << "2^" << i << " = " << uint32_pow(2, i) << std::endl;
        }

        // Test large exponents
        std::cout << "2^30 = " << uint32_pow(2, 30) << std::endl;
        std::cout << "2^31 = " << uint32_pow(2, 31) << std::endl;

        // Test the bias calculation for different bit widths
        uint32_t bias32 = calculate_bias(8);
        std::cout << "32-bit bias: " << bias32 << std::endl;
        assert(127 == bias32); // 2^(8 - 1) - 1 = 127

        uint32_t bias16 = calculate_bias(5);
        std::cout << "16-bit bias: " << bias16 << std::endl;
        assert(15 == bias16); // 2^(5 - 1) - 1 = 15

        uint32_t bias8 = calculate_bias(3);
        std::cout << "8-bit bias: " << bias8 << std::endl;
        assert(3 == bias8); // 2^(3 - 1) - 1 = 3

        // Attempting a negative exponent (should throw an exception)
        std::cout << "2^-1 = " << uint32_pow(2, -1) << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
