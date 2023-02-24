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

// Prototype for function checking if a cycle will be created when locking pairs
bool circle_check(int winner, int loser);

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
    // Look for a candidate called name
    for (int i = 0; i < candidate_count; i++)
    {
        // If match, ranks[] array updates so ranks[rank] is equal to i and return true.
        if (strcmp(name, candidates[i]) == 0)
        {

            ranks[rank] = i;
            return true;
        }

    }
    // If no candidate called name is found, don't update any ranks and return false.
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Update the 2D preferences array based on this current voter's ranks
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // index into preferences array for ranks[i] and ranks[j]
            // +1 to indicate this voter prefers the candidate ranked at i to the candidates that come after (j).
            preferences[ranks[i]][ranks[j]]++;
        }
        // i iterates to next preferred candidate, and +1s to those indedxed after them in ranked, but not those who came before
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // Add each pair of candidates to the pairs array, as long as one candidate is preferred over the other
    // Update global variable pair_count to be the total number of pairs

    // Iterate through each pair of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If candidate i is preferred to candidate j, pair is added to pairs array with i as winner and j as loser
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // If candidate j is preferred to candidate i, pair is added to pairs array with j as winner and i as loser
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].loser = i;
                pairs[pair_count].winner = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // sort pairs in decreasing order by strength of victory, using any sorting algorithm you'd like

    for (int i = 0; i < pair_count; i++)
    {
        // temporary pair to allow us to swap pairs[i] and pairs[j]
        pair temp_pair;

        for (int j = i + 1; j < pair_count; j++)
        {
            // exit loops if pairs array is iterated through entirely without any changes being made
            int swapped = 0;

            // if the strength of victory for pairs[j].winner is bigger than that of pairs[i].winner
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {
                // swap them in the pairs array
                temp_pair = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp_pair;
                swapped++;
            }
            // if no swaps were made, the pairs array is sorted and we can break
            if (swapped == 0)
            {
                break;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // starting from the pair ranked at index 0 in pairs array, check if there is a cycle created if we lock in this edge
    for (int i = 0; i < pair_count; i++)
    {
        // if there is no circle createdd
        if (circle_check(pairs[i].winner, pairs[i].loser) == false)
        {
            // lock in the edge
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // initialise count variable to keep track of how many candidates we have checked
        // but inside outer loop so it resets upon each completion of inner loop
        int count = 0;

        // compare them to every other candidate;
        for (int j = i + 1; j < candidate_count; j++)
        {
            // check if any other candidate beat the winner of the pair
            // if they didn't, update counter to indicate candidate i has been checked against another candidate
            if (locked[j][i] == false)
            {
                count++;
            }
        }
        // if count has reached (candidate_count - 1) when above loop is finished
        // then we found no locked edges pointing at candidate i
        if (count == candidate_count - 1)
        {
            // they can be assumed to be the source of the graph and thus the winner
            // print out their name.
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

bool circle_check(int winner, int loser)
{
    // Recursive function to check for a cycle before locking

    // if winner == loser, locking in an edge would create a cycle so return true
    if (winner == loser)
    {
        return true;
    }
    // for each pair
    for (int i = 0; i < pair_count; i++)
    {
        // check if our loser beat any other candidate
        if (locked[loser][i] == true)
        {
            // check for locked edge between the winner and the candidate defeated by our loser
            if (circle_check(winner, i) == true)
            {
                // if there is one, a cycle will be created if we lock this edge in
                // return true so lock_pairs function knows not to lock in the edge in this case
                return true;
            }
        }
    }
    // if no circle was found, we can tell lock_pairs to safely lock in the edge.
    return false;
}