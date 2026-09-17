// Harvard CS50x - Week 1 - Problem Set 1 
// Hello, It’s Me: https://cs50.harvard.edu/x/psets/1/me/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string user_name = get_string("What's your name? "); // Prompt user for name

    printf("hello, %s\n", user_name); // Prints user name

    return 0;
}
