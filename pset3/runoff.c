#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9
#define RANK_SIZE 3

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++) // loop through candidates
    {
        if (strcmp(name, candidates[i].name) == 0) // identify voted candidate
        {
            preferences[voter][rank] = i; // populate matrix with index of voted candidate
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // now we are goint to loop trough the top 3 (j) ranked votes for all voters (i)
    // j = 0 to rank sizee (i.e. TOP 1 to TOP N, N = 3 in this scenario)
    // find the first TOP 3 candidate that is not eliminated and adds 1 vote then exit rank loop
    // go to next voter

    for (int i = 0; i < voter_count; i++) // first loop through all voters quantity
    {
        for (int j = 0; j < RANK_SIZE; j++) // second loop trough top 3 votes
        {
            int voted_candidate = preferences[i][j]; // atributes an index (just for visualization)
            if (!candidates[voted_candidate].eliminated) // checks if the candidate is eliminated
            {
                candidates[voted_candidate].votes += 1; // if candidate is not elimaned then vote plus 1
                break; // if vote plus 1 then break second loop
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority = voter_count / 2; // decimal is not important
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = voter_count; // initiate from max number of votes and go down from here
    for (int i = 0; i < candidate_count; i++) // loop trough candidates
    {
        if (!candidates[i].eliminated && candidates[i].votes < min) // keeps the smaller number of votes from non eliminated candidates
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++) // loop throug candidates
    {
        if (!candidates[i].eliminated
            && candidates[i].votes > min) // checks if some non eliminate candidate has more than the mininum votes
        {
            return false; // (i.e. not all candidates has the same votes count)
        }
    }
    return true; // if neither of non eliminated candidates is above minimum, by exclusion, they all have same vote count
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++) // loop through candidates
    {
        if (!candidates[i].eliminated
            && candidates[i].votes <= min) // check if the non yet eliminated candidate votes is under the minimum needed
        {
            candidates[i].eliminated = true; // eliminate candidate
        }
    }
    return;
}
