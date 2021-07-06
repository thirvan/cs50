import cs50


def main():
    height = 0
    # Prompt user to enter the height
    while height < 1 or height > 8:
        height = cs50.get_int("Height ")

    for row in range(height):

        # Print gap before hashes
        for col in range(height - row - 1):
            print(" ", end="")

        # Print left hashes
        print_hashes(row)

        # Print gap between hashes
        print("  ", end="")

        # Print right hashes
        print_hashes(row)

        print()


def print_hashes(n):
    for i in range(n + 1):
        print("#", end="")


main()