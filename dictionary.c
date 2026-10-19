// Harvard CS50x - Week 5 - Problem Set 5 
// Speller: https://cs50.harvard.edu/x/psets/5/speller/

// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// hash table by 2 first letters
const unsigned int N = 26 * 26;

// Hash table
node *table[N];

int word_count = 0;
bool loaded = false;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    for (node *ptr = table[index]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
            return true;
    }
    return false;
}

// Hashes word to a index based on 2 first letters
// Single word as first character ("a" in same index of "aa")
// Possesive goes as last character ("a's" in same index of "az")
unsigned int hash(const char *word)
{
    if (strlen(word) == 1)
        return (toupper(word[0]) - 'A') * 26;

    else if (isalpha(word[1]))
        return ((toupper(word[0]) - 'A') * 26) + (toupper(word[1]) - 'A');

    else
        return (toupper(word[0]) - 'A') * 26 + 25; // for possessive as "a's"
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *input = fopen(dictionary, "r");
    if (input == NULL)
    {
        printf("Could not open dictionary\n");
        return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(input, "%s", buffer) != EOF)
    {
        int index = hash(buffer);

        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Could not malloc new dictionary word\n");
            return false;
        }

        strcpy(new_node->word, buffer);
        new_node->next = table[index];
        table[index] = new_node;
        word_count++;
    }

    fclose(input);
    loaded = true;
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (loaded)
    {
        return word_count;
    }
    else
        return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }
    return true;
}
