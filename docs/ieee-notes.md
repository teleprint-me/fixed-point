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
