# Harvard CS50x - Week 6 - Problem Set 6 
# DNA: https://cs50.harvard.edu/x/psets/6/dna/
# longest_match function provided by Harvard

import csv
import sys


def main():
    """Finds a match between a person DNA with a provided Dataset of people&STRs"""
    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Incorrect command-line arguments: python dna.py database.csv sequence.txt")
        sys.exit(1)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as file:
        sequence = file.read()

    # Read database file into a variable
    with open(sys.argv[1]) as file:
        database = csv.DictReader(file)
        str_keys = list(database.fieldnames)  # str_keys may vary from databases

        # Find longest match of each STR in DNA sequence
        person_str = {}
        for key in str_keys:  # just search for str inside database
            person_str[key] = longest_match(sequence, key)

        # Check database for matching profile
        for person in database:
            for database_str in str_keys[1:]:  # database keys start with person's name
                if int(person[database_str]) != person_str[database_str]:
                    break
            else:  # if the loop reached its end (w/o breaking)
                print(f"{person["name"]}")
                sys.exit(0)

        print("No match")
        sys.exit(0)


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in sequence, return longest run found
    return longest_run


main()
