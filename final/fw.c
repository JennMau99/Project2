#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"
#include <ctype.h>

/* Global variables */
Word **hashtable;
int tablesize;
int tableitems;

/* Definitions of the functions used */
Word *hash_node(char *s, int freq);
unsigned int hash_code(char *s);
Word **make_table(int size);
void hash_words(int f, char **a, int b);
Word **resize(Word **hashtable);
int get_index(unsigned int hashval, char *s, int resize);
Word **sort(Word **hashtable);
int compare(const void *a, const void *b);
void print_table(int wordnum);

/* Creates a new hashtable of size and returns a pointer to it. */
Word **make_table(int size)
{
	int i = 0;
	Word **newtable = (Word**)malloc(size *sizeof(Word*));
	for(i = 0; i < size; i++)
        {
                newtable[i] = NULL;
        }
	tablesize = size;
	return newtable;
}
/* Prints the top n words of the table in order of frequency.
 * If two words have the same frequency, they are printed in reverse alphabetical order. */
void print_table(int wordnum)
{
	int i = tablesize - 1;
	int a = wordnum;
	int maxwidth = 9;
	fprintf(stderr, "The top %d words (out of %d) are:\n", wordnum, tableitems);
 	while(i >= 0 && a > 0)
        {
		
                if(hashtable[i] != NULL){
                        fprintf(stderr, "%*d %s\n",maxwidth, hashtable[i]->frequency, hashtable[i]->word);
						free(hashtable[i]->word);
            	 		a--;
				}
				free(hashtable[i]);
                i--;
        }
		free(hashtable);
}

/* The main() of fw.c.
 * 1) Processes args.
 * 2) Calls hash_words() to create the hashtable.
 * 3) Calls sort() to sort the hashtable.
 * 4) Calls print_table() to print the top values from the hashtable.
 * */
int main(int argc, char **argv)
{
	int wordnum = 10;	
	int filenames = 0;
	if(argc > 1 && (strcmp(argv[1], "-n") == 0))
	{
		if(argc > 2 && atoi(argv[2]) != 0)
		{
			wordnum = atoi(argv[2]);	
			filenames = 3;
		}
		else
		{
			fprintf(stderr, "usage fw [-n num] [ file1 [ file 2 ...] ]");
			return 1;
		}
	}
	else if(argc == 1)
	{
		filenames = 0;
	}
	else if (argc > 0)
	{
		filenames = 1;
	}

 	hash_words(filenames, argv, argc);
	hashtable = sort(hashtable);
	print_table(wordnum);



	return 0;
}
/* Compare function for the stdlib qsort function.
 * It's passed as a pointer to qsort.
 * 1) If two words are both NULL, they are equal.
 * 2) If one word is NULL, the word that isn't NULL comes before it.
 * 3) If two words have the same frequency, the one that comes later
 * 		in the alphabet is ordered first.
 * 4) If two words have different frequencies, the one with the higher
 * 		frequency is ordered first.
 * */
int compare(const void *a, const void *b)
{
	int i = 0;
	const Word *word1 = *(const Word **)a;
	const Word *word2 = *(const Word **)b;
	if (word1 == NULL && word2 == NULL)
		return 0;
	if (word1 == NULL)
		return 1;
	if (word2 == NULL)
		return -1;
	if (word1->frequency == word2->frequency)
	{
		while (word1->word[i] == word2->word[i])
			i++; 
		return (word1->word[i] - word2->word[i]);
	}
	return (word1->frequency - word2->frequency);
}
/* Uses the stdlib qsort (quicksort) to sort the hashtable.
 * Also uses the compare() function to compare Words in the hashtable. */
Word **sort(Word **hashtable)
{
	qsort(hashtable, tablesize, sizeof(Word*), compare);
	return hashtable;
}
