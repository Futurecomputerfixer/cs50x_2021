// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
//Number of buckets in hash table
const unsigned int N = 675;
int sizenode = 0;
// Hash table
node *table[N] = {NULL};

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int x = hash(word);
    node *cursor = table[x];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        cursor = cursor ->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int a = tolower(word[0]);
    int b = 97;
    if (word[1] != '\0')
    {
        b = tolower(word[1]);
    }
    int x = a - 97;
    int y = b - 97;
    int z = 26 * x + y;
    return z;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        temp -> next = NULL;
        strcpy(temp -> word, buffer);
        int x = hash(buffer);
        if (table[x] == NULL)
        {
            table[x] = temp;
        }
        else
        {
            temp -> next = table[x];
            table[x] = temp;
        }
        sizenode++;
    }
    fclose(file);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return sizenode;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int a = 0 ; a < N ; a++)
    {
        node *cursor = table[a];
        node *tmp = table[a];
        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
