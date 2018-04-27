#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"
#include <ctype.h>

/* Allocates space for a new Word and returns a pointer to it. */
Word* hash_node(char *s, int freq)
{
	Word * new_node = (Word*)(malloc(sizeof(Word)));
	new_node->word = malloc(strlen(s) + 1);
	strcpy(new_node->word, s);
	new_node->frequency = freq;
	return new_node;
}
/* Calculates the hash value for a given token (word). */
unsigned int hash_code(char *s)
{
	unsigned int hashval;
	/* We have to change this line here */
	/*
	if(s == NULL)
	{
		return NULL;
	}
	*/
	for(hashval = 0; *s != '\0'; s++)
	{
		hashval = *s + 31 * hashval;
	}
	return hashval % tablesize;

}   
/* Handles collisions in the hashtable by recalculating their index. */
int get_index(unsigned int hashval, char *s, int resize)
{
	int i = 0;
	/* Unnecessary comparison- this shouldn't be NULL since it's an int */
	while (1)
	{
		if(resize == 1 && hashtable[((hashval + i * i) % tablesize)] != NULL)
		{
		/*only enters if not being resize*/	
			if(strcmp(hashtable[((hashval + i * i) % tablesize)]->word, s) == 0)
                	{
				return ((hashval + i * i) % tablesize);
                        }
                }
		else if(hashtable[((hashval + i * i) % tablesize)] == NULL)
		{
			return ((hashval + i*i) % tablesize);
		}
		
		i++;
	}
}

