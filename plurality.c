#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2; //Use return 2 here instead of return 1 for distinct false exit codes
    }
    for (int i = 0; i < candidate_count; i ++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i ++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i ++)
    {
        // not strcmp(argv[i], name because passing through string name in "//Loop over all voters" for loop inside main
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highest_vote_count = 0; // used to store the highest vote count associated with a particular candidate
    int num_winners = 0; // store the number of winning candidates, especially if there's more than one winner
    string winner[candidate_count]; // stores the names of the winning candidate(s) with (max) size candidate_count
                                    // in the case where every candidate has the same number of votes; unused positions in array = NULL
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].votes > highest_vote_count)
        {
            highest_vote_count = candidates[i].votes;
            winner[0] = candidates[i].name; // start at 0 and not i because highest vote count may not be at i = 0
            num_winners = 1; // not ++ because highest vote count changes as iterate through candidate array
        }
        else if (candidates[i].votes == highest_vote_count)
        {
            winner[num_winners] = candidates[i].name; // e.g. if 3 winners then num_winners = 2 or 3rd position in winner[]
            num_winners ++; // must be after store extra name into winner[]
        }
    }
    for (int i = 0; i < num_winners; i ++)
    {
        printf("%s\n", winner[i]);
    }
    return;
}