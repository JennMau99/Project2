#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"

/*struct word {
	char *word;
	int frequency;
};

typedef struct word Word;
*/
static Word **hashtable;
int tablesize;
int tableitems;

Word *hash_node(char *s, int freq);
unsigned int hash_code(char *s);
Word **make_table(int size);
void hash_words(int f, char **a, int b);
void delete(Word **hashtable, int size);
Word **resize(Word **hashtable);
int get_index(unsigned int hashval, char *s, int resize);
Word **sort(Word **hashtable);
int compare(const void *a, const void *b);
void print_table(int wordnum);

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
void print_table(int wordnum)
{
	int i = tablesize - 1;
	int a = wordnum;
	fprintf(stderr, "The top %d words (out of %d) are:\n", wordnum, tableitems);
 	while(i >= 0 && a > 0)
        {
		
                if(hashtable[i] != NULL){
                        fprintf(stderr, "\t%d %s\n", hashtable[i]->frequency, hashtable[i]->word);
             		a--;
		}
                i--;
        }

	
}
void printtable(Word **hashtable)
{
        int i = 0;
        while(i < tablesize)
        {
                if(hashtable[i] != NULL){
                        fprintf(stderr, hashtable[i]->word);
                        fprintf(stderr, "2nd\n");
                }

                i++;
        }
}
void hash_words(int filename, char **argv, int argc)
{
	FILE *fp;
	char *token;
	char str[100];
	int size = 2;
	unsigned int index;

	hashtable = make_table(size);
	while(filename < argc)
	{
		fp = fopen(argv[filename], "r");
	
		if(fp == NULL)
		{
			fprintf(stderr, "ERROR");
		}
		while((fgets (str, 100, fp) != NULL))
		{
			token = strtok(str, " \n");
			while( token != NULL ) {
				if((tableitems/tablesize) > 0.5)
				{
					hashtable = resize(hashtable);
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
		fclose(fp);
		filename++;
		
	}
	
}

Word* hash_node(char *s, int freq)
{
	Word * new_node = (Word*)(malloc(sizeof(Word)));
	new_node->word = malloc(strlen(s) + 1);
	strcpy(new_node->word, s);
	new_node->frequency = freq;
	return new_node;
}

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

int get_index(unsigned int hashval, char *s, int resize)
{
	int i = 0;
	/* Unnecessary comparison- this shouldn't be NULL since it's an int */
	int *a;		
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
	else if(argc > 0)
	{
		filenames = 1;
	}

 	hash_words(filenames, argv, argc);
	hashtable = sort(hashtable);
	print_table(wordnum);



	return 0;
}

	
/* Resize function for the hashtable.
 * 1) Calculate new table size.
 * 2) Create new hashtable.
 * 3) Rehash the words from the old table.
 * 4) Handle collisions.
 * 5) Free old table.
 * 6) Return pointer to new hashtable.
 */

int get_index_resize(Word **table, unsigned int hashval, char *s)
{
        int i = 0;
        /* Unnecessary comparison- this shouldn't be NULL since it's an int */
        int *a;
        while (1)
        {
                if(table[((hashval + i * i) % tablesize)] == NULL)
                {
                        return ((hashval + i*i) % tablesize);
                }

                i++;
        }
}

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

	}
	delete(oldtable, oldsize);
	/*hashtable = newtable;
	tablesize = newSize;
	print_table();*/
	return newtable;
}

void delete(Word **hashtable, int size)
{
	while (size > 0)
	{
		size--;
		free(hashtable[size]);
	}
}

/* Quicksort algorithm */
int compare(const void *a, const void *b)
{
	const Word *word1 = *(const Word **)a;
	const Word *word2 = *(const Word **)b;
	if (word1 == NULL && word2 == NULL)
		return 0;
	if (word1 == NULL)
		return 1;
	if (word2 == NULL)
		return -1;
	return (word1->frequency - word2->frequency);
}

Word **sort(Word **hashtable)
{
	qsort(hashtable, tablesize, sizeof(Word*), compare);
	return hashtable;
}
