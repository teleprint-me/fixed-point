# IEEE-754 Notes

## Floating-Point Binary Formats

IEEE-754 defines five basic formats, but this document will focus on three binary formats, excluding the decimal formats as they are out of scope.

- The three primary binary formats defined by IEEE-754 are 32-bit, 64-bit, and 128-bit.

The specification also allows for extended formats. In addition to the standard formats, this document will include the 16-bit format, Google Brain float (B16), and a custom 8-bit float implementation for computational efficiency.

- This document will cover 32-bit, 16-bit, B16, and 8-bit float representations. Some examples may include 64-bit representations for visual comparison and added contextual clarity.

### Specification conformance

- We need to provide a way to initialize, encode, decode, and free the information.

Other conformance options are typically hardware and/or language dependent:

- Providing expected arithmetic formats
- Providing the ability to read and write formats
- Providing radix formats (base 2 and base 10)

The last three points seem superfluous, especially considering that base 2, 10, and 16 are all utilized.

## Specification levels

There are 4 levels defined by the specification:

1. **Extended Real Numbers**: $\{-\infty, \dots, 0, \dots, +\infty\}$

   Extended real numbers ($\mathbb{R}$) encompass all possible results obtained through mathematical operations on real numbers, approximated as finite floating-point values.

2. **Floating-Point Data**: $\{-\infty, \dots, +\infty\} \cup \{-\infty, +\infty\} \cup (\text{qNaN} \cup \text{sNaN})$

   Floating-point data form an algebraically closed system including signed zeros, nonzero finite numbers (both positive and negative), infinities, and NaNs. This level represents a many-to-one mapping from extended real numbers due to rounding errors.

3. **Floating-Point Representation**: $(s, e, m) \cup \{-\infty, +\infty\} \cup (\text{qNaN} \cup \text{sNaN})$

   Representations of floating-point data include sign ($s$), exponent ($e$), mantissa ($m$, also known as significand), along with positive infinity, negative infinity, QuietNaN (qNaN), and SignalingNaN (sNaN). This level provides a one-to-many mapping from floating-point data to their representations due to different encodings.

4. **Bit-String Representation**: $1010 \ 1100$

   Bit-string representation encodes each representation of floating-point data in a specific format, potentially mapping multiple representations to the same bit string or vice versa.

### Floating-point representation

Representations can consist of:

- **$(s, e, m)$ in radix $b$ (base)**: Expressed as $(-1)^s \times b^e \times m$,
  
  where:
  - $s$ is the sign,
  - $e$ is the exponent,
  - $m$ is the mantissa (also known as the significand).

- **$\{-\infty, +\infty\}$**: 

  The mathematical basis of IEEE-754 includes the extended reals, which encompass real numbers along with positive and negative infinity.

- **$\text{qNaN} \cup \text{sNaN}$**:

  NaN (Not-a-Number) values are used to represent results of invalid operations or undefined quantities. These include QuietNaN (qNaN) for operations with indeterminate results and SignalingNaN (sNaN) for exceptional conditions that may trigger an interrupt or exception.

## Set of representable numbers

The specification defines this as a finite set of floating-point numbers within a given format. Each format may include the parameters $b$, $p$, $emax$, and $emin$.

I like to think of this as base ($b$), precision ($p$), the exponents maximum ($max(e)$), and the exponents minimum ($min(e)$) where $min(e)$ is $1 - max(e)$ for all formats.

- $b = 2$ or $b = 10$ where $b$ is the base
- $p = len(m)$
- $emax = max(e)$
- $emin = min(e)$ where $1 - max(e)$ for all formats

Each format is identified by its base and the number of bits in its encoding.

| precision | sign bit | exponent bits     | mantissa bits                                                    |
| --------- | -------- | ----------------- | ---------------------------------------------------------------- |
| 64-bit    | 0        | 000 0000 0000     | 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 0000 |
| 32-bit    | 0        |     0000 0000     |                                     000 0000 0000 0000 0000 0000 |
| 16-bit    | 0        |        0 0000     |                                                     00 0000 0000 |
| B16-bit   | 0        |     0000 0000     |                                                         000 0000 |
| 8-bit     | 0        |           000     |                                                             0000 |
