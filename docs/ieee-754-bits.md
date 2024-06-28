# Bit-width representations
NOTE: This is a WIP (Work in Progress).

## 32-BIT FLOATING POINT FORMAT IEEE-754

| SIGN BIT | 8-BIT EXPONENT | 23-BIT MANTISSA           |
| -------- | -------------- | ------------------------- |
| 1        | 10000011       | 0111100 01100000 00000000 |

- EXAMPLE: -23.546875
- HEX: 0xc1bc6000
- value = (-1)^sign · 2^(exponent - bias) · mantissa

### Understanding IEEE-754

1. **Components**: A floating-point number in IEEE-754 format consists of three parts:
    - **Sign bit**: Indicates positive or negative.
    - **Exponent**: Determines the range of the number.
    - **Mantissa (or significand)**: The precision part of the number.

2. **Representation**: The standard representation for a floating-point number is:

    (-1)^sign · 2^(exponent - bias) · mantissa

    The exponent is 'biased' to handle both positive and negative exponents.

3. **Special Values**: NaN, infinity, and zero are represented using specific patterns in the exponent and mantissa.

### Conversion Between Python Int and Floating-Point values

1. **From Float to Int (Custom Precision)**:
   - **Extract Components**: Use `math.frexp()` to break the float into a mantissa and exponent.
   - **Normalize and Scale**: Adjust the mantissa and exponent according to your custom precision. This involves scaling and possibly rounding the mantissa, and adjusting the exponent with a custom bias.
   - **Pack into Int**: Combine the sign, exponent, and mantissa into an integer using bitwise operations.

2. **From Int to Float**:
   - **Extract Components**: Use bitwise operations to extract the sign, exponent, and mantissa from the integer.
   - **De-normalize**: Adjust the exponent and mantissa back to their original scale. This involves adding the bias back to the exponent and converting the mantissa back to a fraction.
   - **Construct the Float**: Combine these components back into a floating-point number.

A table may be useful for visualizing the bit allocation for different floating-point precisions. Let's fill in the details for each precision:

```
| precision | sign bit | exponent bits     | mantissa bits                                                    |
| --------- | -------- | ----------------- | ---------------------------------------------------------------- |
| 64-bit    | 0        | 000 0000 0000     | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |
| 32-bit    | 0        |     0000 0000     |                                     000 0000 0000 0000 0000 0000 |
| 16-bit    | 0        |        0 0000     |                                                     00 0000 0000 |
| B16-bit   | 0        |     0000 0000     |                                                         000 0000 |
| 8-bit     | 0        |           000     |                                                             0000 |
```

For more accuracy, the exact bit allocations for standard IEEE-754 floating-point formats are:

- **64-bit (Double-precision)**:
  - Sign bit: 1
  - Exponent bits: 11
  - Mantissa bits: 52

- **32-bit (Single-precision)**:
  - Sign bit: 1
  - Exponent bits: 8
  - Mantissa bits: 23

- **16-bit (Half-precision)**:
  - Sign bit: 1
  - Exponent bits: 5
  - Mantissa bits: 10

- **B16-bit (Half-precision)**:
  - Sign bit: 1
  - Exponent bits: 8
  - Mantissa bits: 7

- **8-bit (Quarter-precision)**:
  - Sign bit: 1
  - Exponent bits: 3
  - Mantissa bits: 4
