// Harvard CS50x - Week 3 - Problem Set 3 
// Tideman: https://cs50.harvard.edu/x/psets/3/tideman/
// Code until line 102 provided by Harvard

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_cycle(int loser, int winner);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // Loop over candidate list
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i; // Voter's ith preference as candidate index

            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Loop over voter's preferences
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        // Loop over remaining voter's preferences
        for (int j = (i + 1); j < candidate_count; j++)
            preferences[ranks[i]][ranks[j]]++;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Loop over candidates list
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        // Loop over remaining candidates list
        for (int j = (i + 1); j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i]) // i wins over j
            {
                pairs[pair_count].winner = i;

                pairs[pair_count].loser = j;

                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j]) // j wins over i
            {
                pairs[pair_count].winner = j;

                pairs[pair_count].loser = i;

                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory - inverted bubble sort
void sort_pairs(void)
{
    int swap = 1; // non-zero value

    while (swap != 0)
    {
        swap = 0; // reset swap counter to 0

        for (int i = (pair_count - 1); i > 0; i--)
        {

            if (preferences[pairs[i].winner][pairs[i].loser] >
                preferences[pairs[i - 1].winner][pairs[i - 1].loser])
            {
                // Swapping i with i - 1
                pair i_temp = pairs[i];

                pairs[i] = pairs[i - 1];

                pairs[i - 1] = i_temp;

                swap++;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Loop over all sorted pairs
    for (int i = 0; i < pair_count; i++)
    {
        if (check_cycle(pairs[i].loser, pairs[i].winner) == 0) // Pair does not close cycle
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Check if a pair closes a cycle
bool check_cycle(int loser, int winner)
{
    // Loop over all previous locked pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // For each locked pairs
            if (locked[i][j] == true) // Winner: i and loser: j
            {
                if (loser == i) // If initial loser is equal to this locked pair's winner
                                // (arrow from initial loser to this pair's winner)
                {
                    if (j == winner) // If this locked pair's loser is equal to initial winner
                                     // (arrow from this pair's loser to inicial winner)
                    {
                        return true; // Creates a cycle
                    }
                    else if (check_cycle(j, winner) ==
                             true)   // Continue to check starting from this pair's loser
                        return true; // initial testing pair closes a cycle
                }
            }
        }
    }
    return false; // initial loser does not lead to any locked pair's winner
}

// Print the winner of the election
void print_winner(void)
{
    bool loser = false;

    // Loop over all candidates list
    for (int i = 0; i < candidate_count; i++)
    {
        loser = false; // Reset loser status

        // Loop over all head-to-head matchups for candidate i
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true) // If candidate i looses any matchup
            {
                loser = true;

                break;
            }
        }
        if (loser == false)
            printf("%s\n", candidates[i]);
    }
    return;
}
