import cs50

height = 0
# Prompt user to enter the height
while height < 1 or height > 8:
    height = cs50.get_int("Height ")

for row in range(height):

    # Print correct number of spaces
    for col in range(height - row - 1):
        print(" ", end="")

    # Print correct number of hash(es)
    for col in range(row + 1):
        print("#", end="")
    print()