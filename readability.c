// Harvard CS50x - Week 2 - Problem Set 2 
// Credit: https://cs50.harvard.edu/x/psets/2/readability/

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_sum_words(string text);

int get_sum_letters(string text);

int get_sum_sentences(string text);

float average_per_100(float a, float b);

int main(void)
{
    // Prompt user for text to be analised
    string text = get_string("Text: ");

    // Calculate text parameters for Coleman-Liau index
    float sum_words = get_sum_words(text); // sum_words as float for division on average_100

    int sum_letters = get_sum_letters(text);

    int sum_sentences = get_sum_sentences(text);

    float L = average_per_100(sum_letters, sum_words);

    float S = average_per_100(sum_sentences, sum_words);

    // Calculate Coleman-Liau index rounded to the nearest integer
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print index value between 1 and 16 grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

// Calculate the number of word in a text
// Input a text as a string
// Word defined by number of blank spaces
// Output the number of words as int
int get_sum_words(string text)
{
    int sum_words = 1; // start at 1 for counting last word (without blank space)

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if isblank (text[i])
        {
            sum_words += 1;
        }
    }

    return sum_words;
}

// Calculate the number of letters in a text
// Input a text as a string
// Output the number of letters as int
int get_sum_letters(string text)
{
    int sum_letters = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if isalpha (text[i])
        {
            sum_letters += 1;
        }
    }

    return sum_letters;
}

// Calculate the number of sentences in a text
// Input a text as a string
// Sentence defined by ended with "." or "?" or "!"
// Output the number of sentences as int
int get_sum_sentences(string text)
{
    int sum_sentences = 0;

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sum_sentences += 1;
        }
    }

    return sum_sentences;
}

// Calculate the average number of "a" per 100 of "b"
// Input and Output as float
float average_per_100(float a, float b)
{
    float average_per_100 = (a / b) * 100;

    return average_per_100;
}
