# Bit-width Representations in IEEE-754 Floating Point

## Introduction

In computing, floating-point arithmetic is essential for performing numerical calculations involving real numbers, especially when these numbers include fractional parts or decimal points. Unlike fixed-point arithmetic, which represents numbers with a fixed number of digits after the decimal point, floating-point arithmetic allows for a much wider range of values, accommodating both very large and very small numbers. This flexibility makes floating-point representation crucial for scientific computing, graphics, and various engineering applications.

To standardize the representation and computation of floating-point numbers across different hardware and software platforms, the Institute of Electrical and Electronics Engineers (IEEE) established the IEEE 754 standard. This standard defines the format for floating-point numbers, ensuring consistent behavior and accuracy in computations.

## Key Aspects of IEEE 754

The IEEE 754 standard specifies the following key aspects of floating-point representation:

1. **Components of a Floating-Point Number**:
   - **Sign Bit**: This single bit indicates the sign of the number. A sign bit of 0 denotes a positive number, while a sign bit of 1 denotes a negative number.
   - **Exponent**: The exponent determines the range or magnitude of the number. It is stored in a biased form, which means a fixed value (the bias) is subtracted from the actual exponent to accommodate both positive and negative exponents.
   - **Mantissa (or Significand)**: The mantissa represents the precision or significant digits of the number. For normalized numbers, an implicit leading bit (usually 1) is assumed, allowing for an extra bit of precision.

2. **Binary Interchange Formats**:
   - The IEEE 754 standard defines binary interchange formats to ensure accurate and consistent exchange of floating-point data between different computer systems. These formats encode each floating-point number using the sign bit, biased exponent, and trailing significand fields.

3. **Precision Levels**:
   - IEEE 754 specifies different precision levels for floating-point numbers, including 16-bit (half-precision), 32-bit (single-precision), 64-bit (double-precision), and 128-bit (quadruple-precision). This document focuses on 32-bit, 16-bit, and 8-bit (quarter-precision) precision formats.

4. **Special Values**:
   - The standard also defines special values such as positive and negative zero, infinity, and NaN (Not a Number) to handle exceptional cases in floating-point computations.

By understanding these key aspects, we can gain a deeper insight into how floating-point numbers are represented and manipulated in computer systems, particularly in the context of C programming.

---

## Next Steps

From here, we can dive into the structure of floating-point numbers, exploring how the sign bit, exponent, and mantissa are used to represent a wide range of values. We'll also look at the binary interchange formats for different precision levels and provide examples to illustrate the concepts. Additionally, we'll cover conversion between floating-point and integer representations in C to solidify our understanding.

## 32-BIT FLOATING POINT FORMAT (SINGLE PRECISION)

### Structure

| Sign Bit | 8-bit Exponent | 23-bit Mantissa         |
| -------- | -------------- | ----------------------- |
| 1        | 10000011       | 0111100 01100000 00000000 |

- **Example Value**: -23.546875
- **Hex Representation**: 0xc1bc6000
- **Formula**: \((-1)^{\text{sign}} \times 2^{(\text{exponent} - \text{bias})} \times \text{mantissa}\)

### Understanding IEEE-754 Components

1. **Components**:
    - **Sign bit**: Indicates the sign of the number (0 for positive, 1 for negative).
    - **Exponent**: Determines the range (magnitude) of the number.
    - **Mantissa (or significand)**: Contains the precision (significant digits) of the number.

2. **Representation**:
    - The standard formula for a floating-point number is:
      \[ \text{value} = (-1)^{\text{sign}} \times 2^{(\text{exponent} - \text{bias})} \times 1.\text{mantissa} \]
    - The exponent is biased to handle both positive and negative exponents. For single precision, the bias is 127.

3. **Special Values**:
    - **NaN** (Not a Number): Exponent is all 1s, and mantissa is non-zero.
    - **Infinity**: Exponent is all 1s, and mantissa is zero.
    - **Zero**: Both exponent and mantissa are zero.

### Conversion Between Float and Int (Custom Precision)

#### Step 1: Extract Components

In C, we can extract the components of a floating-point number using bit manipulation. For IEEE-754 floating-point representation, we can break the float into its sign, exponent, and mantissa components.

Here’s an example for a 32-bit float:

```c
#include <stdint.h>
#include <math.h>

typedef union {
    float f;
    uint32_t u;
} float32_t;

void extract_float_components(float value, int *sign, int *exponent, int *mantissa) {
    float32_t fu;
    fu.f = value;

    *sign = (fu.u >> 31) & 0x1;                      // Extract sign bit
    *exponent = ((fu.u >> 23) & 0xFF) - 127;         // Extract exponent and unbias
    *mantissa = fu.u & 0x7FFFFF;                     // Extract mantissa (23 bits)
    *mantissa |= 0x800000;                           // Add the implicit leading 1
}
```

#### Step 2: Normalize and Scale

Next, we need to adjust the mantissa and exponent according to the desired custom precision.

```c
#include <stdio.h>

void normalize_and_scale(int *mantissa, int *exponent, int mantissa_bits, int bias) {
    // Normalize the mantissa and scale it
    *mantissa = (*mantissa >> (23 - mantissa_bits));  // Adjust mantissa to fit in the custom bit size
    *mantissa &= (1 << mantissa_bits) - 1;            // Ensure it fits within the specified bit width
    *exponent += bias;                                // Adjust the exponent with the custom bias
}
```

#### Step 3: Pack into Int

Finally, we combine the sign, exponent, and mantissa into a single integer.

```c
uint32_t pack_float_components(int sign, int exponent, int mantissa, int exponent_bits, int mantissa_bits) {
    uint32_t packed_int = 0;

    packed_int |= (sign << (exponent_bits + mantissa_bits)); // Insert sign bit
    packed_int |= ((uint32_t)exponent << mantissa_bits);     // Insert exponent
    packed_int |= (uint32_t)mantissa;                        // Insert mantissa

    return packed_int;
}
```

### Putting It All Together

Here’s the full code for converting a 32-bit float to a custom-precision integer:

```c
#include <stdint.h>
#include <math.h>
#include <stdio.h>

typedef union {
    float f;
    uint32_t u;
} float32_t;

void extract_float_components(float value, int *sign, int *exponent, int *mantissa) {
    float32_t fu;
    fu.f = value;

    *sign = (fu.u >> 31) & 0x1;                      // Extract sign bit
    *exponent = ((fu.u >> 23) & 0xFF) - 127;         // Extract exponent and unbias
    *mantissa = fu.u & 0x7FFFFF;                     // Extract mantissa (23 bits)
    *mantissa |= 0x800000;                           // Add the implicit leading 1
}

void normalize_and_scale(int *mantissa, int *exponent, int mantissa_bits, int bias) {
    // Normalize the mantissa and scale it
    *mantissa = (*mantissa >> (23 - mantissa_bits));  // Adjust mantissa to fit in the custom bit size
    *mantissa &= (1 << mantissa_bits) - 1;            // Ensure it fits within the specified bit width
    *exponent += bias;                                // Adjust the exponent with the custom bias
}

uint32_t pack_float_components(int sign, int exponent, int mantissa, int exponent_bits, int mantissa_bits) {
    uint32_t packed_int = 0;

    packed_int |= (sign << (exponent_bits + mantissa_bits)); // Insert sign bit
    packed_int |= ((uint32_t)exponent << mantissa_bits);     // Insert exponent
    packed_int |= (uint32_t)mantissa;                        // Insert mantissa

    return packed_int;
}

uint32_t float_to_custom_int(float value, int exponent_bits, int mantissa_bits, int bias) {
    int sign, exponent, mantissa;

    extract_float_components(value, &sign, &exponent, &mantissa);
    normalize_and_scale(&mantissa, &exponent, mantissa_bits, bias);

    return pack_float_components(sign, exponent, mantissa, exponent_bits, mantissa_bits);
}

int main() {
    float value = 3.14f;
    int exponent_bits = 8;   // Example for 32-bit float
    int mantissa_bits = 23;  // Example for 32-bit float
    int bias = 127;          // Example bias for 32-bit float

    uint32_t custom_int = float_to_custom_int(value, exponent_bits, mantissa_bits, bias);

    printf("Custom int representation: 0x%X\n", custom_int);

    return 0;
}
```

This code provides a clear example of converting a 32-bit float to a custom-precision integer representation in C. Adjust the `exponent_bits`, `mantissa_bits`, and `bias` values as needed for your specific custom precision.

### From Int to Float

1. **Extract Components**:
    - Use bitwise operations to extract the sign, exponent, and mantissa from the integer.
      ```python
      sign = (packed_int >> (exponent_bits + mantissa_bits)) & 1
      exponent = (packed_int >> mantissa_bits) & ((1 << exponent_bits) - 1)
      mantissa = packed_int & ((1 << mantissa_bits) - 1)
      ```

2. **De-normalize**:
    - Adjust the exponent and mantissa back to their original scale by adding the bias back to the exponent and converting the mantissa back to a fraction.
      ```python
      bias = 127  # Example for 32-bit
      adjusted_exponent = exponent - bias
      normalized_mantissa = 1 + (mantissa / (2 ** mantissa_bits))
      ```

3. **Construct the Float**:
    - Combine these components back into a floating-point number.
      ```python
      float_value = (-1) ** sign * normalized_mantissa * (2 ** adjusted_exponent)
      ```

## Bit Allocation Table for Different Precisions

### Standard IEEE-754 Formats

| Precision         | Sign Bit | Exponent Bits | Mantissa Bits |
| ----------------- | -------- | ------------- | ------------- |
| 64-bit (Double)   | 1        | 11            | 52            |
| 32-bit (Single)   | 1        | 8             | 23            |
| 16-bit (Half)     | 1        | 5             | 10            |

### Custom Formats

| Precision         | Sign Bit | Exponent Bits | Mantissa Bits |
| ----------------- | -------- | ------------- | ------------- |
| B16-bit (Half)    | 1        | 8             | 7             |
| 8-bit (Quarter)   | 1        | 3             | 4             |

### Visualizing Formats

```
| precision | sign bit | exponent bits     | mantissa bits                                                    |
| --------- | -------- | ----------------- | ---------------------------------------------------------------- |
| 64-bit    | 0        | 000 0000 0000     | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |
| 32-bit    | 0        |     0000 0000     |                                     000 0000 0000 0000 0000 0000 |
| 16-bit    | 0        |        0 0000     |                                                     00 0000 0000 |
| B16-bit   | 0        |     0000 0000     |                                                         000 0000 |
| 8-bit     | 0        |           000     |                                                             0000 |
```