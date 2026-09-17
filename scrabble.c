// Harvard CS50x - Week 2 - Problem Set 2 
// Scrabble: https://cs50.harvard.edu/x/psets/2/scrabble/

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Scrabble score for each word from a to z
const int SCRABBLE[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                        1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_score(string word);

int main(void)
{
    // Prompt user for both player's words
    string word_1 = get_string("Player 1: ");

    string word_2 = get_string("Player 2: ");

    // Calculate the word score based on SCRABBLE table
    int score_1 = get_score(word_1);

    int score_2 = get_score(word_2);

    // Compare scores for a winner or tie
    if (score_1 > score_2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score_2 > score_1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Calculate the word score based on SCRABBLE table
// Input a word and sums each character score with SCRABBLE table
// islower() and isupper() rejects non-letter characters
// Output word's score
int get_score(string word)
{
    int score = 0;

    for (int i = 0, len = strlen(word); i < len; i++)
    {
        if (islower(word[i]) != 0) // lowercase letters
        {
            score += SCRABBLE[word[i] - 'a'];
        }
        else if (isupper(word[i]) != 0) // uppercase letters
        {
            score += SCRABBLE[word[i] - 'A'];
        }
    }

    return score;
}
