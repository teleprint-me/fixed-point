# | Character | Byte order             | Size     | Alignment |
# | --------- | ---------------------- | -------- | --------- |
# | @         | native                 | native   | native    |
# | =         | native                 | standard | none      |
# | <         | little-endian          | standard | none      |
# | >         | big-endian             | standard | none      |
# | !         | network (= big-endian) | standard | none      |

import argparse
import struct

parser = argparse.ArgumentParser()

# Add options for different input types
parser.add_argument(
    "-f",
    "--float",
    help="A floating-point number to convert and pack into bits",
)
parser.add_argument(
    "-i",
    "--int",
    help="An integer number to convert and pack into bits",
)
parser.add_argument(
    "-x",
    "--hex",
    help="A hexadecimal string to unpack from bits and display as an integer or float",
)
parser.add_argument(
    "-o",
    "--order",
    default="<",
    help="The byte order to use. Default is `<` (little endian).",
)
args = parser.parse_args()

# Safely handle byte order symbols and default if an invalid value is given
order = {
    "@": "@",
    "=": "=",
    "<": "<",
    ">": ">",
    "!": "!",
}.get(args.order, "<")

# Convert inputs based on the given input type
if args.float is not None:
    packed = struct.pack("<f", float(args.float))
elif args.int is not None:
    packed = struct.pack("<i", int(args.int))
elif args.hex:
    value = int(args.hex, 16)
    if -2147483648 <= value <= 2147483647:
        raise ValueError(f"{value} is out of range.")
    print("int:", value)
    packed = struct.pack("<i", value)
else:
    raise ValueError("Invalid parameter given.")

bits = "".join(f"{byte:08b}" for byte in packed)
nibs = " ".join([bits[i : i + 4] for i in range(0, len(bits), 4)])
print("0b", nibs)
