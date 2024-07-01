# | Character | Byte order             | Size     | Alignment |
# | --------- | ---------------------- | -------- | --------- |
# | @         | native                 | native   | native    |
# | =         | native                 | standard | none      |
# | <         | little-endian          | standard | none      |
# | >         | big-endian             | standard | none      |
# | !         | network (= big-endian) | standard | none      |

import argparse
import struct


def get_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
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
    # Define possible byte order values
    VALID_ORDER = ["<", ">", "@", "=", "!"]
    parser.add_argument(
        "-o",
        "--order",
        choices=VALID_ORDER,
        default="@",
        help="The byte order to use. Default is `@` (native).",
    )
    return parser.parse_args()


def main():
    args = get_arguments()

    # Convert inputs based on the given input type
    if args.float is not None:
        packed = struct.pack(f"{args.order}f", float(args.float))
    elif args.int is not None:
        packed = struct.pack(f"{args.order}i", int(args.int))
    elif args.hex:
        value = int(args.hex, 16)
        if not (-2147483648 <= value <= 2147483647):
            raise ValueError(f"Out of Range: -2147483648 <= {value} <= 2147483647")
        print("int:", value)
        packed = struct.pack(f"{args.order}i", value)
    else:
        raise ValueError("Invalid parameter given.")

    bits = "".join(f"{byte:08b}" for byte in packed)
    nibs = " ".join([bits[i : i + 4] for i in range(0, len(bits), 4)])
    print("0b", nibs)


if __name__ == "__main__":
    main()
