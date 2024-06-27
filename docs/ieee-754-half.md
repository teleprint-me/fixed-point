## IEEE-754 Floating Point Conversion Utility

### Overview
This utility provides functions to encode and decode floating-point numbers between IEEE-754 32-bit (single-precision) and 16-bit (half-precision) formats. The main functions are:
- `encode_float`: Encodes a float to its IEEE-754 binary32 representation.
- `decode_float`: Decodes an IEEE-754 binary32 representation to a float.
- `encode_float16`: Converts a float to its IEEE-754 binary16 (half-precision) representation.
- `decode_float16`: Converts an IEEE-754 binary16 representation to a float.

### Data Types
- `float32_t`: Union for 32-bit floating-point numbers (single-precision).
- `float16_t`: Typedef for 16-bit floating-point numbers (half-precision).

### Functions
1. **Encoding and Decoding 32-bit Floats**
   ```c
   uint32_t encode_float(float value);
   float decode_float(uint32_t bits);
   ```

   These functions use a union (`float32_t`) to encode a float into its IEEE-754 binary32 representation and decode a binary32 representation back into a float.

2. **Encoding and Decoding 16-bit Floats**
   ```c
   uint16_t encode_float16(float value);
   float decode_float16(uint16_t bits);
   ```

   These functions convert between IEEE-754 binary16 (half-precision) and binary32 (single-precision) formats. The `encode_float16` function handles normalization and denormalization, while `decode_float16` does the reverse.

3. **Printing Binary Representation**
   ```c
   void print_binary(uint32_t num);
   ```

   This utility function prints the binary representation of a 32-bit integer, facilitating the visualization of encoded float bits.

### Example Usage
The following example demonstrates encoding and decoding the value of π (pi) in both single and half-precision formats.

#### Main Function
```c
int main() {
    float value = PI;

    uint32_t ef32 = encode_float(value);
    printf("PI (float): %.8f\n", value);
    printf("float32_t encoded (hex): 0x%08X\n", ef32);
    printf("float32_t encoded (binary): ");
    print_binary(ef32);
    float df32 = decode_float(ef32);
    printf("float32_t decoded (float): %.8f\n", df32);

    // Encode the float into IEEE-754 binary16 representation
    uint16_t ef16 = encode_float16(value);
    printf("float16_t encoded (hex): 0x%04X\n", ef16);
    printf("float16_t encoded (binary): ");
    print_binary(ef16);

    // Decode the IEEE-754 binary16 representation back into a float
    float df16 = decode_float16(ef16);
    printf("float16_t decoded (float): %.8f\n", df16);

    return 0;
}
```

### Detailed Description

#### Encoding a 32-bit Float
```c
uint32_t encode_float(float value) {
    float32_t f32;
    f32.value = value;
    return f32.bits;
}
```
This function uses a union to directly access the bit representation of a float.

#### Decoding a 32-bit Float
```c
float decode_float(uint32_t bits) {
    float32_t f32;
    f32.bits = bits;
    return f32.value;
}
```
Similar to `encode_float`, this function uses a union to convert a 32-bit integer representation back to a float.

#### Encoding a 16-bit Float
```c
uint16_t encode_float16(float value) {
    const float scale_to_inf  = decode_float(UINT32_C(0x77800000)); // Upper bound
    const float scale_to_zero = decode_float(UINT32_C(0x08800000)); // Lower bound

    const float saturated_f = fabsf(value) * scale_to_inf;
    float       base        = saturated_f * scale_to_zero;

    const uint32_t f      = encode_float(value);
    const uint32_t shl1_f = f + f;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    uint32_t       bias   = shl1_f & UINT32_C(0xFF000000);
    if (bias < UINT32_C(0x71000000)) {
        bias = UINT32_C(0x71000000);
    }

    base = decode_float((bias >> 1) + UINT32_C(0x07800000)) + base;
    const uint32_t bits = encode_float(base);
    const uint32_t exp_bits = (bits >> 13) & UINT32_C(0x00007C00);
    const uint32_t mantissa_bits = bits & UINT32_C(0x00000FFF);
    const uint32_t nonsign = exp_bits + mantissa_bits;

    return (sign >> 16) | (shl1_f > UINT32_C(0xFF000000) ? UINT16_C(0x7E00) : nonsign);
}
```
This function handles the conversion of a single-precision float to half-precision by scaling, bias adjustment, and bit manipulation.

#### Decoding a 16-bit Float
```c
float decode_float16(uint16_t bits) {
    const uint32_t f      = (uint32_t) bits << 16;
    const uint32_t sign   = f & UINT32_C(0x80000000);
    const uint32_t shl1_f = f + f;

    const uint32_t exp_offset = UINT32_C(0xE0) << 23;
    const float    exp_scale = decode_float(UINT32_C(0x7800000));
    const float    normalized_value = decode_float((shl1_f >> 4) + exp_offset) * exp_scale;

    const uint32_t magic_mask = UINT32_C(126) << 23;
    const float    magic_bias = 0.5f;
    const float    denormalized_value = decode_float((shl1_f >> 17) | magic_mask) - magic_bias;

    const uint32_t denormalized_cutoff = UINT32_C(1) << 27;
    const uint32_t result = sign
                            | (shl1_f < denormalized_cutoff ? encode_float(denormalized_value)
                                                            : encode_float(normalized_value));
    return decode_float(result);
}
```
This function handles the conversion of a half-precision float back to single-precision by scaling, bias adjustment, and bit manipulation.

### Conclusion
This utility provides a comprehensive approach to converting floating-point numbers between IEEE-754 single-precision and half-precision formats. The functions utilize bit manipulation and scaling to ensure accurate conversion while handling special cases like infinity and denormalized numbers.

### References
- IEEE-754 Standard for Floating-Point Arithmetic: [Link](https://ieeexplore.ieee.org/document/8766229)
- Tutorial on IEEE-754 Floating Point Numbers: [GeeksforGeeks](https://www.geeksforgeeks.org/ieee-standard-754-floating-point-numbers/)
- Source Code Repository: [FP16 GitHub](https://github.com/Maratyszcza/FP16)
