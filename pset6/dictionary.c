/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

#define LIMIT 26

// define node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// initialize hash table
node *table[LIMIT];

//initialize dictionary word counter
unsigned int dict_count;

/*
 * Takes a string and returns a hash value
 * based on the first char of the string
 */
unsigned int hash(char *str)
{
    int hashnum = str[0] - 97;
    return hashnum % LIMIT;
}




/*
 * Returns true if word is in dictionary else false.
 */

bool
check(const char *word)
{
    // determine word length
    int len = strlen(word);
    
    // initialize char array to store word
    char wrd[len + 1];
    
    // iterate through word
    for (int i = 0; i < len; i++)    
    {
        if (isalpha(word[i]))
        {
            wrd[i] = tolower(word[i]); // convert word to lowercase
        } else if (word[i] == '\'') 
            wrd[i] = '\'';             // account for apostrophes
    }    
    
    // add terminating character
    wrd[len] = '\0';
    
    // hash word to know where to search in table
    int hnum = hash(wrd);
    
    // initialize pointer to traverse linked list
    node *cond = table[hnum];
    
    // search nodes for matching string
    while (cond != NULL)
    {
        if (strncmp(wrd, cond->word, len + 1) == 0)
            return true;
        cond = cond->next;
    }
    
    // no match found
    return false;
}

/*
 * Loads dict into memory.  Returns true if successful else false.
 */

bool
load(const char *dict)
{
    int index = 0;        // word length counter
    char wrd[LENGTH+1]; // string storage for word
    dict_count = 0;        // word counter
    
    // open dictionary file
    FILE *dptr = fopen(dict, "r");
    if (dptr == NULL) {
        return false;
    }
    
    // find each word in file; char by char
    for (int c = fgetc(dptr); c != EOF; c = fgetc(dptr))
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            wrd[index] = c;
            index++;

            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(dptr)) != EOF && isalpha(dptr));

                // prepare for new word
                index = 0;
            }
        } 
        
        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            wrd[index] = '\0';
                   
            // prepare for next word
            index = 0;
        
            // allocate memory for new node
            node *newptr = malloc(sizeof(node));
            if (newptr == NULL) {
                return false;
            }
            
            // add (word & next) values to node
            for (int i = 0; i < LENGTH + 1; i++)
            {
                
                newptr->word[i] = wrd[i];
                newptr->next = NULL;
            }
            
            // determine hash value for table address
            int hnum = hash(newptr->word);

            // insert node to table using linked lists for collisions
            if (table[hnum] == NULL){
                table[hnum] = newptr;
            } else {
                newptr->next = table[hnum]->next;
                table[hnum]->next = newptr;
            }
            
            // increment word counter
            dict_count++;
        }    
    }  
    
    // close dictionary file
    fclose(dptr);
    return true;
}



/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int
size(void)
{
    /* for debugging purposes */
    // prints number of nodes in each hash table address
    for (int i = 0; i < LIMIT; i++)
    {
        int count = 0;
        node *cond = table[i];
        while (cond != NULL)
        {
            count++;
            cond = cond->next;
        }    
        printf("\n%d nodes in table address %d\n", count, i);
    }
    
    // return words in dictionary
    return dict_count;
}

/*
 * Recursive function for freeing malloc memory
 */
void
fnode(node *tab)
{
  // keep freeing last node of linked list
  if(tab->next != NULL)
    fnode(tab->next);
  free(tab);
}

/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool
unload()
{
    // traverse hash table and free nodes
    for(int i = 0; i < LIMIT; i++)
    {
      if(table[i] != NULL)
        fnode(table[i]);
    }
    return true;
}

