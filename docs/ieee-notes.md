# IEEE-754 Notes

## Floating-Point Binary Formats

IEEE-754 defines five basic formats, but this document will focus on three binary formats, excluding the decimal formats as they are out of scope.

- The three primary binary formats defined by IEEE-754 are 32-bit, 64-bit, and 128-bit.

The specification also allows for extended formats. In addition to the standard formats, this document will include the 16-bit format, Google Brain float (B16), and a custom 8-bit float implementation for computational efficiency.

- This document will cover 32-bit, 16-bit, B16, and 8-bit float representations. Some examples may include 64-bit representations for visual comparison and added contextual clarity.

### Conformance

- We need to provide a way to initialize, encode, decode, and free the information.

Other conformance options are typically hardware and/or language dependent:

- Providing expected arithmetic formats
- Providing the ability to read and write formats
- Providing radix formats (base 2 and base 10)

The last three points seem superfluous, especially considering that base 2, 10, and 16 are all utilized.

## Specification levels

There are 4 levels defined by the specification.

1. Extended real numbers, e.g. $\{-\infty \dots 0 \dots +\infty\}$

    The extended real numbers ($\mathbb{R}$), which include positive and negative infinity, represent all possible results that can be obtained through mathematical operations on real numbers using rounding to approximate them as finite floating-point values.

2. Floating-point data, e.g. $\{-∞ \dots +∞\} \cup \{-∞, +∞\} \cup qNaN \cup sNaN$

    Floating-point data is an algebraically closed system consisting of signed zeros, nonzero finite numbers (both positive and negative), infinities, and NaNs. This level represents a many-to-one mapping from the extended real numbers to floating-point data due to rounding errors.

3. Float-point representation, e.g. $(s, e, m) \cup \{-∞, +∞\} \cup qNaN \cup sNaN$

    Representations of floating-point data consist of sign ($s$), exponent ($e$), and mantissa ($m$, aka the significand), along with positive infinity ($), negative infinity, QuietNaN (qNaN), and SignalNaN (sNaN). This level provides a one-to-many mapping from floating-point data to their representations due to different encodings.

4. Bit-string representation, e.g. $1010 1100$

    Bit strings represent the encoding of each representation of floating-point data in a specific format, which might map multiple representations to the same bit string or vice versa.
