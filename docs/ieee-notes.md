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

Defined as a finite set of floating-point numbers within a format. Parameters: $b$, $p$, $emax$, and $emin$.

- Base ($b$), precision ($p$), maximum exponent ($emax$), minimum exponent ($emin = 1 - emax$).

- $b = 2$ or $b = 10$ (base)
- $p = \text{len}(m)$ (number of significand digits)
- $emax = \max(e)$
- $emin = \min(e) = 1 - emax$

Each format is identified by its base and the number of bits in its encoding.

### Floating-Point Data Representation

This section expands on the floating-point representation, taking the formatted data into account.

- **$(s, e, m)$ in radix $b$ (base)**: $(-1)^s \times b^e \times m$
  - $s$: sign (0 or 1)
  - $e$: exponent ($\min(e) \le e \le \max(e)$)
  - $m$: mantissa (significand) is $d_0 \cdot d_1 \cdot d_2 \cdot \dots \cdot d_{p-1}$
  - $\{±\infty\}$: the upper and lower bounds for a set including infinity
  - $NaN$: $qNaN$ (Quiet NaN) and $sNaN$ (Signaling NaN)

These are the only data representations available.


| precision | sign bit | exponent bits | mantissa bits                                                    |
| --------- | -------- | ------------- | ---------------------------------------------------------------- |
| 64-bit    | 0        | 0000 0000 000 | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |
| 32-bit    | 0        | 0000 0000     | 0000 0000 0000 0000 0000 000                                     |
| 16-bit    | 0        | 0000 0        | 0000 0000 00                                                     |
| B16-bit   | 0        | 0000 0000     | 0000 000                                                         |
| 8-bit     | 0        | 000           | 0000                                                             |
