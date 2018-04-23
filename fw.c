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

Word *hash_node(char *s);
unsigned int hash_code(char *s);
Word **make_table(int size);
void hash_words(int f, char **a, int b);
void delete(Word **hashtable, int size);
Word **resize(Word **hashtable);
int get_index(unsigned int hashval);
Word **sort(Word **hashtable);
int compare(const void *a, const void *b);
void print_table();

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
void print_table()
{
	int i = 0;
 	while(i < tablesize)
        {
                if(hashtable[i] != NULL){
                        fprintf(stderr, hashtable[i]->word);
                        fprintf(stderr, "\n");
                }

                i++;
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
	char *copy;
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
					fprintf(stderr, "resized\n");
					hashtable = resize(hashtable);
				}
			/*	IRR: if(get_index(hash_code(token), token) != -1){
			*/
				index = get_index(hash_code(token));		
				hashtable[index] = hash_node(token); 				
				fprintf(stderr, "%d %s\n", index, hashtable[index]->word);
					
				
				tableitems++;
				token = strtok(NULL, " \n");

			}
		}
		fclose(fp);
		filename++;
		
	}
	
	print_table();
}

Word* hash_node(char *s)
{
	Word * new_node = (Word*)(malloc(sizeof(Word)));
	new_node->word = malloc(strlen(s) + 1);
	strcpy(new_node->word, s);
	new_node->frequency = 1;
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

int get_index(unsigned int hashval)
{
	int i = 0;
	/* Unnecessary comparison- this shouldn't be NULL since it's an int */
	
	while (1)
	{
		if(hashtable[((hashval + i * i) % tablesize)] == NULL)
		{
			return ((hashval + i*i) % tablesize);
		}
		/*if(strcmp(hashtable[((hashval + i * i) % tablesize)]->word, s) == 0)
		{
			fprintf(stderr, "MATCH");
			return -1;
		}*/
		
		i++;
	}
}




int main(int argc, char **argv)
{
	int wordnum = 10;	
	int filenames = 0;
	int i = 0;
	if(argc > 2 && (strcmp(argv[1], "-n") == 0))
	{
		wordnum = argv[2][0];
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
	fprintf(stderr, "%d tablesize \n", tablesize);
	/*hashtable = sort(hashtable);
	while (*wordnum > 0 i < tablesize)
	{
		printf("%d %s", hashtable[tablesize - i - 1]->frequency, hashtable[tablesize - i - 1]->word);
		i++, wordnum--;
		if(hashtable[i] == NULL)
		{
			fprintf(stderr, "NULL");
		}
		else
		{
			fprintf(stderr, hashtable[i]->word);
		}
		i++;
		
	}*/



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


Word **resize(Word **hashtable)
{
	Word **temp;
	int newSize = tablesize * 2 + 1;
	int oldsize = tablesize;
	int forDeleting = tablesize;
	Word **newtable;
	unsigned int hash;
	/* This also sets tablesize to newSize */
	newtable = make_table(newSize);

	while (oldsize > 0)
	{
		oldsize--;
		/* Checks to make sure the index being checked has a Word */
		if(hashtable[oldsize] != NULL){
			
			hash = hash_code(hashtable[oldsize]->word);
			/*fprintf(stderr, "%d hashcode \n", hash);*/
			if (newtable[hash % tablesize] != NULL)
				hash = get_index(hash_code(hashtable[oldsize]->word));
			/*fprintf(stderr, "%d new index \n", hash);*/
			if(hash != -1){
				newtable[hash] = hash_node(hashtable[oldsize]->word);
			}
		}

	}
	/*delete(hashtable, forDeleting);*/
	hashtable = newtable;
	/*tablesize = newSize;
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
	if (a == NULL && b == NULL)
		return 0;
	if (a == NULL)
		return 1;
	if (b == NULL)
		return -1;
	return (((Word*)b)->frequency - ((Word*)a)->frequency);
}

Word **sort(Word **hashtable)
{
	qsort(hashtable, tablesize, sizeof(Word*), compare);
	return hashtable;
}
