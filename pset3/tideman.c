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
int winner_count[MAX];

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool check_cicle(int a, int b, int c);

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
    // rank = posicao de preferencia do eleitor, ranks = quem ta na posicao
    for (int n = 0; n < candidate_count; n++)
    {
        if (strcmp(name, candidates[n]) == 0)
        {
            ranks[rank] = n;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // candidate i over candidate j
    for (int i = 0; i < candidate_count ; i++)
    {
        for (int j = i + 1; j < candidate_count ; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
//            printf("candidatos %s x %s contagem: %i\n", candidates[ranks[i]], candidates[ranks[j]], preferences[ranks[i]][ranks[j]]);
        }
    }
    printf("\n");
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0 ; i < candidate_count; i++)
    {
        for (int j = i + 1 ; j < candidate_count ; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
//                printf("pair made %s x %s\n", candidates[i], candidates[j]);
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
//                printf("pair made %s x %s\n", candidates[j], candidates[i]);
            }
        }
    }
    printf("\n");
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int sort = 0;

    for (int i = 0; i < pair_count ; i++)
    {
        if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[i + 1].winner][pairs[i + 1].loser])
        {
            int temp = pairs[i].winner;
            pairs[i].winner = pairs[i + 1].winner;
            pairs[i + 1].winner = temp;

            temp = pairs[i].loser;
            pairs[i].loser = pairs[i + 1].loser;
            pairs[i + 1].loser = temp;
            sort++;
        }
    }

    if (sort == 0)
    {
        printf("\n");
        return;
    }
    sort_pairs();
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // // locked[i][j] means i is locked in over j
    for (int i = 0  ; i < pair_count; i++)
    {
        if (!check_cicle(pairs[i].winner, pairs[i].loser, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            winner_count[pairs[i].loser]++;
        }
    }


    return;
}

bool check_cicle(int a, int b, int c)
{
    printf("%s pair with %s is %i\n", candidates[a], candidates[b], locked[a][b]);
    if (locked[a][b])
    {
        return true;
    }
    for (int i  = 0; i < pair_count ; i++)
    {
        if (locked[i][a])
        {
            if (check_cicle(i, b, c) || i == c)
            {
                return true;
            }
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (winner_count[i] == 0)
        {
            printf("%s\n", candidates[i]);
        }
    }

    return;
}