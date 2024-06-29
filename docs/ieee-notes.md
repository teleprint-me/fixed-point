# IEEE-754 Notes

## Floating-Point Binary Formats

IEEE-754 defines five basic formats, but this document will focus on three binary formats, excluding the decimal formats as they are out of scope.

- Primary binary formats: 32-bit, 64-bit, and 128-bit.

The specification allows for extended formats, including a 16-bit format, Google Brain float (B16), and a custom 8-bit float for computational efficiency.

- Covered formats: 32-bit, 16-bit, B16, and 8-bit. Examples may include 64-bit for visual comparison and context.

### Specification Conformance

- Provide methods to initialize, encode, decode, and free information.

Other conformance options, typically hardware/language dependent:
- Expected arithmetic formats
- Ability to read/write formats
- Radix formats (base 2 and base 10)

The last three points may be redundant as base 2, 10, and 16 are all utilized.

## Specification Levels

Four levels defined by the specification:

1. **Extended Real Numbers**: $\{-\infty, \dots, 0, \dots, +\infty\}$

   Extended real numbers ($\mathbb{R}$) encompass all possible results from mathematical operations on real numbers, approximated as finite floating-point values.

2. **Floating-Point Data**: $\{-\infty, \dots, +\infty\} \cup \{-\infty, +\infty\} \cup (\text{qNaN} \cup \text{sNaN})$

   Algebraically closed system including signed zeros, nonzero finite numbers, infinities, and NaNs. Represents a many-to-one mapping from extended real numbers due to rounding errors.

3. **Floating-Point Representation**: $(s, e, m) \cup \{-\infty, +\infty\} \cup (\text{qNaN} \cup \text{sNaN})$

   Representations include sign ($s$), exponent ($e$), mantissa ($m$), positive infinity, negative infinity, QuietNaN (qNaN), and SignalingNaN (sNaN). One-to-many mapping from floating-point data to their representations due to different encodings.

4. **Bit-String Representation**: $1010 \ 1100$

   Encodes floating-point data in a specific format, potentially mapping multiple representations to the same bit string or vice versa.

### Floating-Point Representation

Representations can consist of:

- **$(s, e, m)$ in radix $b$ (base)**: $(-1)^s \times b^e \times m$
  - $s$: sign
  - $e$: exponent
  - $m$: mantissa (significand)

- **$\{-\infty, +\infty\}$**: 
  - Mathematical basis includes real numbers with positive/negative infinity.

- **$\text{qNaN} \cup \text{sNaN}$**:
  - NaNs represent invalid operations or undefined quantities. qNaN for indeterminate results, sNaN for exceptional conditions that may trigger an interrupt/exception.

## Set of Representable Numbers

Defined as a finite set of floating-point numbers within a format. Parameters: $b$, $p$, $max(e)$, and $min(e)$.

- Base ($b$), precision ($p$), maximum exponent ($max(e)$), minimum exponent ($min(e) = 1 - max(e)$).

- $b = 2$ or $b = 10$ (base)
- $p = len(m)$ (number of significand digits)
- $max(e) = max(e)$
- $min(e) = min(e) = 1 - max(e)$

Each format is identified by its base and the number of bits in its encoding.

### Floating-Point Data Representation

This section expands on the floating-point representation, taking the formatted data into account.

- **$(s, e, m)$ in radix $b$ (base)**: $(-1)^s \times b^e \times m$
  - $s$: sign (0 or 1)
  - $e$: exponent ($\min(e) \le e \le \max(e)$)
  - $m$: mantissa (significand) is $d_0 \cdot d_1 \cdot d_2 \cdot \dots \cdot d_{p-1}$
  - $\{\pm\infty\}$: the upper and lower bounds for a set including infinity
  - $NaN$: $qNaN$ (Quiet NaN) and $sNaN$ (Signaling NaN)

These are the only data representations available.

### Relationship Between Views

In the previous description, the significand $m$ is viewed in a scientific form, with the radix point immediately following the first digit. For certain purposes, it’s convenient to view the significand as an integer $c$. The finite floating-point numbers can then be described as follows:

- **Signed Zero and Non-Zero Floating-Point Numbers**: In the form $(-1)^s \times b^q \times c$, where:
  - $s$ is 0 or 1 (sign).
  - $q$ is an integer such that $\text{min(e)} \le q + (p - 1) \le \text{max(e)}$.
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

- **Conversion from $c$ to $m$**:
  - $m = c \times b^{1 - p}$
  - Here, $p$ is the precision, or the number of digits in the significand.

- **Conversion from $m$ to $c$**:
  - $c = m \times b^{p - 1}$

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

### Determining the Range

- The smallest positive normal floating-point number is $b^{e_{min}}$.
- The largest is $b^{e_{max}} \times (b - b^{1 - p})$.
- Subnormal numbers have magnitudes less than $b^{e_{min}}$ and fewer than $p$ significant digits.

### Representing Zero and Infinity

- Zero: Both +0 and -0 have distinct representations and significance in operations like division by zero.
- Infinity: Represented without a sign when the sign is not important.

### Parameters for Common Formats

#### 16-bit (Half-precision)

- **Total bits**: 16
- **Sign bit**: 1 bit
- **Exponent bits**: 5 bits
- **Significand bits**: 10 bits

#### B16 (Brain-precision, custom format)

- **Total bits**: 16
- **Sign bit**: 1 bit
- **Exponent bits**: 8 bits
- **Significand bits**: 7 bits

#### 8-bit (Quarter-precision, custom format)

- **Total bits**: 8
- **Sign bit**: 1 bit
- **Exponent bits**: 3 bits
- **Significand bits**: 4 bits

#### Calculation of $e_{max}$

For a given format, the maximum exponent value ($e_{max}$) is determined as follows:

$e_{max} = 2^{(\text{exponent bits} - 1)} - 1$

### Parameters for Common Formats

| Parameter   | 8-bit | 16-bit | B16  | 32-bit | 64-bit | 128-bit |
| ----------- | ----- | ------ | ---- | ------ | ------ | ------- |
| $p$, digits | 4     | 11     | 7    | 24     | 53     | 113     |
| $e_{max}$   | +3    | +15    | +127 | +127   | +1023  | +16383  |

### Explanation

- **8-bit format**: 
  - $p$ (digits) = 4 (significand bits)
  - Exponent bits = 3
  - $e_{max} = 2^{(3 - 1)} - 1 = 3$

- **16-bit format**: 
  - $p$ (digits) = 11 (significand bits)
  - Exponent bits = 5
  - $e_{max} = 2^{(5 - 1)} - 1 = 15$

- **B16 format**: 
  - $p$ (digits) = 7 (significand bits)
  - Exponent bits = 8
  - $e_{max} = 2^{(8 - 1)} - 1 = 127$

- **32-bit format**: 
  - $p$ (digits) = 24 (significand bits)
  - Exponent bits = 8
  - $e_{max} = 2^{(8 - 1)} - 1 = 127$

- **64-bit format**: 
  - $p$ (digits) = 53 (significand bits)
  - Exponent bits = 11
  - $e_{max} = 2^{(11 - 1)} - 1 = 1023$

- **128-bit format**: 
  - $p$ (digits) = 113 (significand bits)
  - Exponent bits = 15
  - $e_{max} = 2^{(15 - 1)} - 1 = 16383$

### Outline for Common Precision Formats

| precision | sign bit | exponent bits | mantissa (or significand) bits                                   |
| --------- | -------- | ------------- | ---------------------------------------------------------------- |
| 64-bit    | 0        | 0000 0000 000 | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |
| 32-bit    | 0        | 0000 0000     | 0000 0000 0000 0000 0000 000                                     |
| B16-bit   | 0        | 0000 0000     | 0000 000                                                         |
| 16-bit    | 0        | 0000 0        | 0000 0000 00                                                     |
| 8-bit     | 0        | 000           | 0000                                                             |
