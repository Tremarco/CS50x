// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
// somewhat arbitrary number of buckets; not ideal but serves for now
const unsigned int N = 4000;

// Hash table
node *table[N];

// initialise variable for counting number of words in the dictionary
int size_of_dictionary = 0;

// prototype for recursive function to free_list in each bucket later
void free_list(node *n);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // initialise local variable and set it as the hash_value of whatever word we want to search for
    int hash_value = hash(word);

    // go to that bucket in our hash table
    node *n = table[hash_value];

    // loop through the elements of the linked list in that bucket until we reach the end (indicated by n being NULL)
    while (n != NULL)
    {
        // if the word matches the word stored in the node we are looking at
        if (strcasecmp(word, n->word) == 0)
        {
            // then the word is in the dictionary
            return true;
        }
        // otherwise go to the next node
        else
        {
            n = n->next;
        }
    }
    // If we complete the loop and the word was not found, return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Initialise variable to store hash number
    int hash_num = 0;

    // Iterate through each letter of the word
    for (int i = 0; i < strlen(word); i++)
    {
        // sum together ascii values of the word to reach a specific total
        hash_num += toupper(word[i]);
    }

    // I originally included this step but it slowed the program down immensely!
    // I suspect that I'm using too many buckets, meaning I get less collisions if I simply don't % N and there are so many it won't go out of range anyway
    // Definitely not optimal but I think satsfies speller criteria well enough to progress with the course for now; may come back later and optimise
    // mod hash number by number of buckets in table to ensure in range, store in appropriate bucket
    // hash_num = hash_num % N;
    return hash_num;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *f = fopen(dictionary, "r");
    // safety check
    if (dictionary == NULL)
    {
        printf("Could not open %s\n", dictionary);
        return false;
    }
    // Initialise the buffer to be LENGTH + 1 to account for sentinal
    char buffer[LENGTH + 1];
    // Until the end of the file, read next word into the buffer
    while (fscanf(f, "%s", buffer) != EOF)
    {
        // create a new node for each word
        node *n = malloc(sizeof(node));
        // Safety check
        if (n == NULL)
        {
            return false;
        }

        // copy the word from the buffer into the node
        strcpy(n->word, buffer);

        // run it through the hash function
        int hash_index = hash(buffer);
        // insert node into the relevant index of the hash table
        // ensure to avoid oprhaning the rest of the linked list by pointing from n to the old "head" first, then assigning the "head" to be n
        n->next = table[hash_index];
        table[hash_index] = n;

        // +1 to size of dictionary variable each time we complete the loop and successfully load in a word
        size_of_dictionary++;

    }

    // close the file and return true to indicate success
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return size_of_dictionary variable (already initialised to 0, so will return 0 if we don't load any words and the number of words otherwise)
    return size_of_dictionary;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // set current node to be the hash bucket corresponding to i
        node *n = table[i];
        // call recursive free_list function
        free_list(n);

        // eventually n should be NULL after recursive function is finished, so at this point return true to indicate this list is finished
        if (n == NULL && i == (N - 1))
        {
            return true;
        }
    }

    // if we reach this point, unload was not successful so return false
    return false;
}

void free_list(node *n)
{
    // base case, if n is NULL just return
    if (n == NULL)
    {
        return;
    }
    // otherwise
    else
    {
        // recursively call free_list on the next element of the linked list
        free_list(n->next);
        // then and only then can we free n itself
        free(n);
    }
}
