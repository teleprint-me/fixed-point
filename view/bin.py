import argparse


def bin_to_int(binary: str) -> int:
    # convert the digits into a sequence of ints
    binary = [int(digit) for digit in binary if digit.isdigit()]

    total = 0
    power = len(binary) - 1

    # Iterate through each bit from least significant to most significant
    for bit in binary:
        total += bit * (2**power)
        power -= 1

    return total


def main():
    parser = argparse.ArgumentParser()

    # Add options for input and output
    parser.add_argument(
        "-b",
        "--binary",
        required=True,
        help="The binary number to convert.",
    )

    args = parser.parse_args()

    result = bin_to_int(args.binary)

    print("Integer:", result)


if __name__ == "__main__":
    main()
