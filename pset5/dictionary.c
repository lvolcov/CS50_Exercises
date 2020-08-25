// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 65536;

// Hash table
node *table[N];
int dictsize = 0;

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    //Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    //variable word from dictionary
    char wfd[LENGTH + 1];
    //Read strings from file one at a time
    while (fscanf(dict, "%s", wfd) != EOF)
    {
        dictsize++;
        //Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, wfd);
        n->next = NULL;
        //hash word to obtain a hash value
        int x = hash(n->word);
        //insert node into hash table at that location
        n->next = table[x];
        table[x] = n;
    }
    fclose(dict);
    return true;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Ref: https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
    unsigned int hash = 0;
    for (int i=0, n=strlen(word); i<n; i++) 
    {
        hash = (hash << 2) ^ tolower(word[i]);
    }
    return hash % N;
    
    
    /*int x = (tolower(word[0]) + 3) * (tolower(word[1]) + 2);
    return x % N;*/
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictsize;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int x = hash(word);
    struct node *cursor;
    //find word
    for (cursor = table[x]; cursor != NULL ; cursor = cursor->next)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}


// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    struct node *tmp;
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}

