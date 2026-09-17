// Harvard CS50x - Week 2 - Problem Set 2 
// Scrabble: https://cs50.harvard.edu/x/psets/2/substitution/

// Subsititution cipher that replaces each letter of a plaintext to another. Encrypted by
// a 26-letter key that sets a new alphabetical order. A key as NQXPOMAFTRHLZGECYJIUWSKDVB
// replaces A as N, B as Q and so on.

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int KEY_LEN = 26;

int main(int argc, string argv[])
{
    // Verify if command-line argument is a single digit (.\substitution key)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");

        return 1;
    }

    string key = argv[1];

    // Verify if key has 26 letters
    if (strlen(key) != KEY_LEN)
    {
        printf("Key must contain 26 letters\n");

        return 1;
    }

    // Verify if key has 26 unique letters and change each one
    // for its position in alphabetical order (a = 1, b = 2, so on...)
    // for both lower and uppercase
    char index_key[KEY_LEN];

    strcpy(index_key, key); // Copy original key for letter-to-index operation

    for (int i = 0; i < KEY_LEN; i++)
    {
        if (islower(key[i]))
        {
            index_key[i] -= 'a'; // subtracts first lowercase letter for calculate
                                 //  its position on alphabetical order
        }
        else if (isupper(key[i]))
        {
            index_key[i] -= 'A'; // subtracts first uppercase letter for calculate
                                 //  its position on alphabetical order
        }
        else
        {
            printf("Key must contain 26 letters\n"); // rejects non-alphabetic

            return 1;
        }

        // verifies letter repetition, comparing to just to previous letters
        for (int j = 0; j < i; j++)
        {
            if (index_key[i] == index_key[j])
            {
                printf("Key letters can't be repeated\n");

                return 1;
            }
        }
    }

    // prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // encrypt plaintext based on key, preserving case
    for (int i = 0, len = strlen(plaintext); i < len; i++)
    {
        if (islower(plaintext[i]))
        {
            plaintext[i] = index_key[plaintext[i] - 'a'] + 'a';
        }
        else if (isupper(plaintext[i]))
        {
            plaintext[i] = index_key[plaintext[i] - 'A'] + 'A';
        }
    }

    // print encrypted plaintext (ciphertext)
    printf("ciphertext: %s\n", plaintext);

    return 0;
}
