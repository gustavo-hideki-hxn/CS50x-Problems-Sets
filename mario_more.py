# Harvard CS50x - Week 6 - Problem Set 6 
# Mario (Python): https://cs50.harvard.edu/x/psets/6/mario/more/
# Python version of week 1 Mario 

from cs50 import get_int

UPPER_PYRAMID_LIMIT = 8  # from Problem Set 6


def main():
    height = get_positive_height()

    for i in range(1, height + 1):
        print(" " * (height - i), end="")
        print("#" * i, end="")
        print(" " * 2, end="")
        print("#" * i, end="")
        print()


def get_positive_height():
    while True:
        height = get_int("Height: ")
        if height > 0 and height <= UPPER_PYRAMID_LIMIT:
            break

    return height


main()
