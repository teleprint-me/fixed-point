import argparse


def print_decimal_hexadecimal_binary(base: int = 2, power: int = 8):
    # Decimal values
    print("| int | hex | bin |")
    print("| --- | --- | --- |")
    for i in range(0, base**power):
        hex_value = "{:02X}".format(i).upper()
        binary_value = bin(i)[2:].zfill(8)
        print("| {:3d} | {:>2s} | {} |".format(i, hex_value, binary_value))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "-b",
        "--base",
        type=int,
        default=2,
        help="The base number used for range end. Default is 2.",
    )
    parser.add_argument(
        "-p",
        "--power",
        type=int,
        default=8,
        help="The exponent number used for range end. Default is 8.",
    )
    args = parser.parse_args()

    print_decimal_hexadecimal_binary(args.base, args.power)


if __name__ == "__main__":
    main()
