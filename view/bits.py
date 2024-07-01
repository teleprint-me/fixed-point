import argparse
import struct

parser = argparse.ArgumentParser()
parser.add_argument(
    "-d",
    "--decimal",
    type=float,
    default=263.3333333333,
    help="A floating-point number to convert and pack into bits",
)
args = parser.parse_args()

# Convert to IEEE-754 format
packed = struct.pack(">f", args.decimal)
bits = "".join(f"{byte:08b}" for byte in packed)

print(bits)
