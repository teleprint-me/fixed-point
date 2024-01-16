/*
    examples/extract_sign_bit.cpp
*/
#include <iostream>
#include <cstring>

// Function to extract the sign bit from a float
int extract_sign_bit(float float_value) {
    // Ensure that the size of float and int are the same
    static_assert(sizeof(float) == sizeof(int), "Float and int must have the same size");

    int sign_bit;
    
    // Copy the bytes of the float into the sign_bit integer
    std::memcpy(&sign_bit, &float_value, sizeof(float));

    // Use bitwise right shift and AND operation to isolate the sign bit
    return (sign_bit >> 31) & 1;
}

int main() {
    float float_value = -12.34; // Replace with your float value

    // Call the extract_sign_bit function to get the sign bit
    int sign_bit = extract_sign_bit(float_value);

    // Check the sign bit value and display the result
    if (sign_bit == 0) {
        std::cout << "The float is positive or zero." << std::endl;
    } else {
        std::cout << "The float is negative." << std::endl;
    }

    return 0;
}
