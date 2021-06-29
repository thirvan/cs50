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
}
pair;

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
void print_winner(void);
int get_victory(int idx);
bool check_cycle(int winner, int loser);

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        // Start loop at i to prevent chekcing already checked pairs
        for (int j = i; j < candidate_count; j++)
        {
            int vote_candidate1 = preferences[i][j];
            int vote_candidate2 = preferences[j][i];

            // Check if there is a winner
            if (vote_candidate1 != vote_candidate2)
            {
                pair newpair;
                // If votes of candidate 1 is stronger than candidate 2
                if (vote_candidate1 > vote_candidate2)
                {
                    newpair.winner = i;
                    newpair.loser = j;
                }
                // If votes of candidate 2 is stronger than candidate 1
                else
                {
                    newpair.winner = j;
                    newpair.loser = i;
                }
                pairs[pair_count] = newpair;
                pair_count++;
            }
        }
    }
}


// Get the strength of victory of a pair in the pairs array at index idx
int get_victory(int idx)
{
    int votes_winner = preferences[pairs[idx].winner][pairs[idx].loser];
    int votes_loser = preferences[pairs[idx].loser][pairs[idx].winner];

    return votes_winner - votes_loser;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int swap = false;
    do
    {
        for (int i = 0; i < pair_count - 1; i++)
        {
            swap = false;
            int victory1 = get_victory(i);
            int victory2 = get_victory(i + 1);
            if (victory1 < victory2)
            {
                pair temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                swap = true;
            }
        }
    }
    while (swap == true);
}

// Check if locking the pair pairs[winner][loser] will create a cyblj
bool check_cycle(int winner, int loser)
{
    if (winner == loser)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[loser][i] == true)
            {
                if (locked[loser][winner] == true)
                {
                    return true;
                }
                else
                {
                    if (check_cycle(winner, i) == true)
                    {
                        return true;
                    }

                }
            }
        }

        return false;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        if (check_cycle(pairs[i].winner, pairs[i].loser) == false)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

