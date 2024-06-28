# IEEE-754 Notes

## Floating-point binary formats

Five basic formats are defined, but we focus on 3 binary formats while exluding the decimal formats as they are out of scope for this document.

- The three binary formats defined by IEEE-754 have a length of 32, 64, and 128-bit formats.

According to the specification, we can extend these formats. The specifications include a 16-bit which is officially defined, but I've also taken the time to include Google Brain float as we a custom 8-bit float implementation.

- This document will include 16, brain 16, and 8-bit formats for computational efficiency.

This document will primarily focus on 32, 16, B16, and 8-bit float representations. Some examples may include 64 bit representations for visual comparison and added contextual clarity.

### Conformance

- We'll need to provide a way to initialize, encode, decode, and free the information.

The other conformance options are typically hardware and/or language dependent.

- Providing expected arithmetic formats
- Providing ability to read and write formats
- Providing radix formats (base 2 and base 10 respectively)

The last 3 points seem superfluous, especially considering base 2, 10, and 16 are all utilized.
