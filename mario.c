// Harvard CS50x - Week 1 - Problem Set 1 
// Mario: https://cs50.harvard.edu/x/psets/1/mario/more/

#include <cs50.h>
#include <stdio.h>

#define UPPER_PYRAMID_LIMIT 8 // Upper limit = 8 defined by Problem Set 1
int get_positive_height(void);
void print_n_times(char c, int n);

// Prints Mario's double pyramid based on height from user
int main(void)
{
    int height = get_positive_height();

    for (int i = 1; i <= height; i++)
    {
        print_n_times(' ', height - i);
        print_n_times('#', i);
        print_n_times(' ', 2);
        print_n_times('#', i);
        printf("\n");
    }
}

// Prompt user a pyramid height between 1 and 8
int get_positive_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > UPPER_PYRAMID_LIMIT);

    return height;
}

// Prints input character n times
void print_n_times(char c, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c", c);
    }
}
