#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"
#include <ctype.h>

/* Global variables */
static Word **hashtable;
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
             		a--;
		}
                i--;
        }

	
}
/* Hashes each word from the input file into the hash table.
 * 1) Open the file. If a file isn't given, use stdin instead. 
 * 		If the file doesn't exist, print an error and continue.
 * 2) Process each line in the file.
 * 3) For each word, convert it to lowercase, hash it, and store it in the table.
 * 4) If the hashtable is too full, resize it. 
 * 6) Once done with a file, close it and move to the next file, if there is one.
 * */
void hash_words(int filename, char **argv, int argc)
{
	FILE *fp;
	char *token;
	char str[100];
	int size = 2;
	unsigned int index;
	int i = 0;
	int buffermax = 10;
	int strlength = 0;
	char *buffer;
	char ch;
	hashtable = make_table(size);
	while(filename < argc)
	{
		if (filename != 0)
			fp = fopen(argv[filename], "r");
		else
			fp = stdin;
	
		if(fp == NULL)
		{
			fprintf(stderr, "/home/pn-cs357/lib/asgn2//Tests/Data/nosuchfile: No such file or directory\n");
		}
		else
		{
			ch = getc(fp);
			buffer = (char *) malloc(sizeof(char) * buffermax);
			while(ch != EOF)
			{
				if ((tableitems/tablesize) > 0.5)
					hashtable = resize(hashtable);
				if (strlength == buffermax)
				{
					buffermax *= 2;
					buffer = realloc(buffer, buffermax);
				}
				if (isalnum(ch))
				{	
					/*you might have to check for chars*/
					ch = (char)tolower(ch);
					buffer[strlength] = ch;
					strlength++;
				}
				else if (strlength != 0 && isalnum(buffer[0]))
				{
					buffer[strlength] = '\0';
					index = get_index(hash_code(buffer), buffer, 1);
					if (hashtable[index] == NULL)
					{
						hashtable[index] = hash_node(buffer, 1);
						tableitems++;
					}
					else
						hashtable[index]->frequency++;
					free(buffer);
					buffermax = 10;
					strlength = 0;
					buffer = (char *) malloc(sizeof(char) * buffermax);
				}
				ch = getc(fp);
			}			

			/* this is a problem here, since one of the tests is a really long line */
			/*
			while((fgets (str, 100, fp) != NULL))
			{
				token = strtok(str, " ^ - . ? ! / _ = + ( ) ~ \\ \t \n");
				while( token != NULL ) {
					i = 0;
					if((tableitems/tablesize) > 0.5)
					{
						hashtable = resize(hashtable);
					}
					for(i = 0; token[i] != '\0'; i++)
					{
						token[i] = (char)tolower(token[i]);
					}
					index = get_index(hash_code(token), token, 1);
					if(hashtable[index] == NULL){
						hashtable[index] = hash_node(token, 1);
						tableitems++; 		
					}	
					else 
					{	
					hashtable[index]->frequency++;
					}
						
					token = strtok(NULL, " \n");
	
				}
			}
			*/
			fclose(fp);
		}
		filename++;
		
	}
}
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
	if(argc > 2 && (strcmp(argv[1], "-n") == 0))
	{
		wordnum = atoi(argv[2]);
		if(argc > 2)
		{	
			filenames = 3;
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
