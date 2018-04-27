#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"
#include <ctype.h>


/* A get_index() function specifically called by resize.
 * Resize can't have the ability to increment a word's frequency,
 * which the other get_index() has. */
int get_index_resize(Word **table, unsigned int hashval, char *s)
{
        int i = 0;
        /* Unnecessary comparison- this shouldn't be NULL since it's an int */
        while (1)
        {
                if(table[((hashval + i * i) % tablesize)] == NULL)
                {
                        return ((hashval + i*i) % tablesize);
                }

                i++;
        }
}
/* Resize function for the hashtable.
 * 1) Calculate new table size.
 * 2) Create new hashtable.
 * 3) Rehash the words from the old table.
 * 4) Handle collisions.
 * 5) Free old table.
 * 6) Return pointer to new hashtable.
 */
Word **resize(Word **hashtable)
{
	int newSize = tablesize * 2 + 1;
	int oldsize = tablesize;
	Word **newtable;
	Word **oldtable;
	unsigned int hash;
	/* This also sets tablesize to newSize */
	newtable = make_table(newSize);
	oldtable = hashtable;
	hashtable = newtable;
	
	while (oldsize > 0)
	{
		oldsize--;
		/* Checks to make sure the index being checked has a Word */
		if(oldtable[oldsize] != NULL){
			hash = hash_code(oldtable[oldsize]->word);
			if (newtable[hash % tablesize] != NULL){
				hash = get_index_resize(newtable, hash_code(oldtable[oldsize]->word), oldtable[oldsize]->word);
			}
			newtable[hash % tablesize] = hash_node(oldtable[oldsize]->word, oldtable[oldsize]->frequency);
		}
		free(oldtable[oldsize]->word);
		free(oldtable[oldsize]);
	}
	free(oldtable);
	return newtable;
}

