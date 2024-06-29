# Notes for Floating-point Precision

## Floating-Point Binary Formats

IEEE-754 defines five basic formats, but this document will focus on three binary formats, excluding the decimal formats as they are out of scope.

- **Primary binary formats**: 32-bit, 64-bit, and 128-bit.

The specification allows for extended formats, including a 16-bit format, Google Brain float (B16), and a custom 8-bit float for computational efficiency.

- **Covered formats**: 32-bit, 16-bit, B16, and 8-bit. Examples may include 64-bit for visual comparison and context.

## Specification

### Conformance

- Provide methods to initialize, encode, decode, and free information.

Other conformance options, typically hardware/language dependent:
- Expected arithmetic formats
- Ability to read/write formats
- Radix formats (base 2 and base 10)

The last three points may be redundant as base 2, 10, and 16 are all utilized.

### Levels

Four levels defined by the specification:

1. **Extended Real Numbers**: $\{-\infty, \dots, 0, \dots, +\infty\}$

   Extended real numbers ($\mathbb{R}$) encompass all possible results from mathematical operations on real numbers, approximated as finite floating-point values.

2. **Floating-Point Data**: $\{-\infty, \dots, +\infty\} \cup \{-\infty, +\infty\} \cup (\text{qNaN} \cup \text{sNaN})$

   Algebraically closed system including signed zeros, nonzero finite numbers, infinities, and NaNs. Represents a many-to-one mapping from extended real numbers due to rounding errors.

3. **Floating-Point Representation**: $(s, e, m) \cup \{-\infty, +\infty\} \cup (\text{qNaN} \cup \text{sNaN})$

   Representations include sign ($s$), exponent ($e$), mantissa ($m$), positive infinity, negative infinity, QuietNaN (qNaN), and SignalingNaN (sNaN). One-to-many mapping from floating-point data to their representations due to different encodings.

4. **Bit-String Representation**: $1010 \ 1100$

   Encodes floating-point data in a specific format, potentially mapping multiple representations to the same bit string or vice versa.

## Floating-Point Representation

Representations can consist of:

- **$(s, e, m)$ in radix $b$ (base)**: $(-1)^s \times b^e \times m$
  - $s$: sign
  - $e$: exponent
  - $m$: mantissa (significand)

- **$\{-\infty, +\infty\}$**: 
  - Mathematical basis includes real numbers with positive/negative infinity.

- **$\text{qNaN} \cup \text{sNaN}$**:
  - NaNs represent invalid operations or undefined quantities. qNaN for indeterminate results, sNaN for exceptional conditions that may trigger an interrupt/exception.

### Set of Representable Numbers

Defined as a finite set of floating-point numbers within a format. Parameters: $b$, $p$, $e_{max}$, and $e_{min}$.

- Base ($b$), precision ($p$), maximum exponent ($e_{max}$), minimum exponent ($e_{min} = 1 - e_{max}$).

- $b = 2$ (use binary base)
- $p = \text{len}(m)$ (number of significand digits)
- $e_{max} = \text{len}(e) - 1$ (one less than the number of exponent digits)
- $e_{min} = 1 - e_{max}$ (one more than the additive inverse of $e_{max}$)

Each format is identified by its base and the number of bits in its encoding.

### Floating-Point Data Representation

This section expands on the floating-point representation, taking the formatted data into account.

- **$(s, e, m)$ in radix $b$ (base)**: $(-1)^s \times b^e \times m$
  - $s$: sign (0 or 1)
  - $e$: exponent ($\text{e}_{min} \le e \le \text{e}_{max}$)
  - $m$: mantissa (significand) is $d_0 \cdot d_1 \cdot d_2 \cdot \dots \cdot d_{p-1}$
  - $\{\pm\infty\}$: the upper and lower bounds for a set including infinity
  - $NaN$: $qNaN$ (Quiet NaN) and $sNaN$ (Signaling NaN)

These are the only data representations available.

## Integer Representation: Relationship Between Views

In the previous description, the significand $m$ is viewed in a scientific form, with the radix point immediately following the first digit. For certain purposes, it’s convenient to view the significand as an integer $c$. The finite floating-point numbers can then be described as follows:

- **Signed Zero and Non-Zero Floating-Point Numbers**: In the form $(-1)^s \times b^q \times c$, where:
  - $s$ is 0 or 1 (sign).
  - $q$ is an integer such that $e_{min} \le q + (p - 1) \le e_{max}$.
  - $c$ is an integer represented by a digit string $d_0 d_1 d_2 \dots d_{p-1}$, where each digit $d_i $ is an integer $0 \le d_i < b$, meaning $c$ satisfies $0 \le c < b^p$.

This integer representation of the significand $c$ and its corresponding exponent $q$ describe exactly the same set of floating-point numbers as the scientific form. For finite floating-point numbers, the relationships are:

- $e = q + (p - 1)$
- $m = c \times b^{1 - p}$

The distinction between $c$ and $m$ lies in how the significand is represented and interpreted in different contexts.

#### $m$: Significand in Scientific Form

- **Scientific Form**: In this representation, the significand $m$ is viewed as a fractional number with the radix point immediately following the first digit.
- **Example**: For a base $b = 2$ and a 3-digit significand, $m$ might be represented as $1.110 \times 2^e$.
- **Mathematical Representation**: $m$ is expressed in a form like $(-1)^s \times b^e \times m$, where $m$ is the fractional part.

#### $c$: Significand as an Integer

- **Integer Form**: In this representation, the significand $c$ is treated as an integer without a fractional component. This is useful for certain computational purposes.
- **Example**: The same 3-digit binary significand might be represented as the integer $1110$.
- **Mathematical Representation**: The number is then represented as $(-1)^s \times b^q \times c$, where $c$ is an integer.

### Relationship and Conversion

Both representations describe the same set of floating-point numbers, but they are formatted differently for different purposes.
  - **$p$ is the precision**: The number of digits in the significand.

- **Conversion from $c$ to $m$**:
  - $m = c \times b^{1 - p}$

- **Conversion from $m$ to $c$**:
  - $c = \frac{m}{b^{p - 1}}$

### Example to Illustrate

Let’s consider a simple example with a base $b = 10$ and precision $p = 3$:

- **Scientific Form**:
  - Suppose $m = 1.23$.
  - This would be expressed as $(-1)^s \times 10^e \times 1.23$.

- **Integer Form**:
  - To convert $m = 1.23$ into an integer form $c$:
    - $c = 1.23 \times 10^{3 - 1} = 1.23 \times 100 = 123$.
  - The number is then expressed as $(-1)^s \times 10^q \times 123$.

So, while $m$ and $c$ represent the same underlying value, $m$ includes the radix point in a fractional form, and $c$ is an integer form used for certain computational efficiencies.

## Calculating $e_{\text{max}}$

- The smallest positive normal floating-point number is $b^{e_{min}}$.
- The largest is $b^{e_{max}} \times (b - b^{1 - p})$.
- Subnormal numbers have magnitudes less than $b^{e_{min}}$ and fewer than $p$ significant digits.

### Parameters for Common Formats

#### 32-bit (Single-precision)

- **Total bits**: 32
- **Sign bit**: 1 bit
- **Exponent bits**: 8 bits (bias = 127)
- **Significand (Mantissa)**: 23 bits

#### BFloat16 (Google Brain float)

- **Total bits**: 16
- **Sign bit**: 1 bit
- **Exponent bits**: 8 bits (bias = 127)
- **Significand (Mantissa)**: 7 bits

#### 16-bit (Half-precision)

- **Total bits**: 16
- **Sign bit**: 1 bit
- **Exponent bits**: 5 bits (bias = 15)
- **Significand (Mantissa)**: 10 bits

#### 8-bit (Quarter-precision)

- **Total bits**: 8
- **Sign bit**: 1 bit
- **Exponent bits**: 4 bits (bias = 7)
- **Significand (Mantissa)**: 3 bits

### Parameters for Common Formats

| Parameter   | 8-bit | 16-bit | B16  | 32-bit | 64-bit | 128-bit |
| ----------- | ----- | ------ | ---- | ------ | ------ | ------- |
| $p$, digits | 4     | 11     | 7    | 24     | 53     | 113     |
| $e_{max}$   | +3    | +15    | +127 | +127   | +1023  | +16383  |

### Outline for Common Precision Formats

| precision | sign bit | exponent bits | mantissa (or significand) bits                                   |
| --------- | -------- | ------------- | ---------------------------------------------------------------- |
| 64-bit    | 0        | 0000 0000 000 | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |
| 32-bit    | 0        | 0000 0000     | 0000 0000 0000 0000 0000 000                                     |
| B16-bit   | 0        | 0000 0000     | 0000 000                                                         |
| 16-bit    | 0        | 0000 0        | 0000 0000 00                                                     |
| 8-bit     | 0        | 000           | 0000                                                             |

## Calculating $e_{\text{min}}$

In floating-point representation, $e_{\text{min}}$ refers to the minimum exponent value allowed for normalized floating-point numbers within a specific format. It is directly related to $e_{\text{max}}$, the maximum exponent value, through the formula:

$e_{\text{min}} = 1 - e_{\text{max}}$

where:
- $e_{\text{max}}$ is the maximum exponent value determined by the number of exponent bits available in the format.

### Example Calculation

For example, consider a format with $e_{\text{max}} = 127$ (common in IEEE-754 single precision):

$e_{\text{min}} = 1 - 127 = -126$

Therefore, $e_{\text{min}}$ for this format would be \(-126\).

### Significance

Understanding $e_{\text{min}}$ is crucial for determining the range of exponents available within a floating-point format. It defines the smallest exponent value that can be represented for normalized numbers, ensuring both positive and negative ranges are adequately covered by the format.

### Representing Zero and Infinity

- Zero: Both +0 and -0 have distinct representations and significance in operations like division by zero.
- Infinity: Represented without a sign when the sign is not important.

### Example of an IEEE-754 Conversion

Let’s convert the decimal number 13.25 to IEEE-754 32-bit format:

1. **Convert to binary**: 13.25 in binary is 1101.01.
2. **Normalize**: 1.10101 × 2^3.
3. **Set sign bit**: 0 (positive number).
4. **Calculate exponent**: 3 + 127 (bias) = 130.
5. **Encode significand**: 10101000000000000000000 (23 bits).

### Converting Binary to IEEE-754

1. **Identify components**: Determine the sign, exponent, and mantissa from the binary string.
2. **Calculate decimal value**: Combine the components to reconstruct the decimal value.

### Example of a 16-bit BFloat Conversion

Let's convert 1.5 to BFloat16:

1. **Convert to binary**: 1.5 in binary is 1.1.
2. **Normalize**: 1.1 × 2^0.
3. **Set sign bit**: 0 (positive number).
4. **Calculate exponent**: 0 + 127 (bias) = 127.
5. **Encode significand**: 1000000 (7 bits).
