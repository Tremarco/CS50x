#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

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
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
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
    // Iterate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // Compare name with each candidates name (not case sensitive to allow more flexibility in vote input)
        if (strcasecmp(name, candidates[i].name) == 0)
        {
            // If names match, +1 to the relevant candidates vote total and return true.
            candidates[i].votes++;
            return true;
        }
    }
    // If no match was found for the vote during the previous loop, return false to indicate invalid vote.
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // Initialise highest_vote variable as 1st candidates vote total
    int highest_vote = candidates[0].votes;

    // Iterate from 2nd candidate to end candidate, checking if they have a higher vote total
    for (int i = 1; i < candidate_count; i++)
    {
        if (candidates[i].votes > highest_vote)
        {
            // If they do have a higher vote total, update the highest_vote variable.
            highest_vote = candidates[i].votes;
        }
    }
    // Again iterate through all candidates
    for (int j = 0; j < candidate_count; j++)
    {
        // print the name of all candidates who received the highest_vote number of votes
        if (candidates[j].votes == highest_vote)
        {
            printf("%s\n", candidates[j].name);
        }
    }

    return;
}