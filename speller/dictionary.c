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

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to get hash value
    unsigned int index = hash(word);

    // Traverse linked list at hashed index
    node *cursor = table[index];

    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true; // Word found
        }
        cursor = cursor->next;
    }

    return false; // Word not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Simple hash function: hash on first letter converted to uppercase
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false; // Could not open file
    }

    // Initialize table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Buffer for storing each word
    char word[LENGTH + 1];

    // Read words from file and add to hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(file);
            return false; // Unable to allocate memory
        }

        strcpy(new_node->word, word);

        // Hash word to get index
        unsigned int index = hash(word);

        // Insert node into hash table at index
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close dictionary file
    fclose(file);

    return true; // Success
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Traverse each bucket in hash table
    for (int i = 0; i < N; i++)
    {
        // Traverse linked list at each bucket
        node *cursor = table[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Traverse each bucket in hash table
    for (int i = 0; i < N; i++)
    {
        // Traverse linked list at each bucket
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    return true; // Success
}
