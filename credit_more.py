# Harvard CS50x - Week 6 - Problem Set 6 
# Credit (Python): https://cs50.harvard.edu/x/psets/6/credit/
# Python version of week 1 Credit

import sys
from cs50 import get_int


def main():
    card_number = get_int("Number: ")  # get_int handles non-numeric input
    card_n_str = str(card_number)  # string format for easier handle with len() and card_n_str[0:2]

    length = len(card_n_str)
    if length < 13 or length > 16:
        print("INVALID")
        sys.exit(1)

    verify_luhn(length, card_number)

    # starting as string avoids a helper function for getting start_numbers
    start_numbers = card_n_str[0:2]

    if length == 15 and (start_numbers == "34" or start_numbers == "37"):
        print("AMEX")

    elif length == 16 and (int(start_numbers) >= 51 and int(start_numbers) <= 55):
        print("MASTERCARD")

    elif ((length == 13 or length == 16) and (int(start_numbers) >= 40 and int(start_numbers) <= 49)):
        print("VISA")

    else:
        print("INVALID")


# Verify checksum according to Luhn's algorithm
# (if incorrect, print INVALID and stop)
def verify_luhn(length, number):
    n = 0

    for i in range(1, length + 1):
        if (i % 2 == 0):  # even digit position
            p = 2 * (number % 10)
            if (p >= 10):
                p = (p // 10) + (p % 10)
            n += p

        else:  # odd digit position
            n = (number % 10) + n

        number = number // 10  # extract the number's last digit for restarting loop

    if (n % 10 != 0):
        print("INVALID")
        sys.exit(1)


main()
