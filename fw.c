#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* #include "fw.h" */

struct word {
	char *word;
	int frequency;
};

typedef struct word Word;

static Word **hashtable;

Word hash_node(char *s);
int hash_code(char *s);
Word **make_table(int size);
void hash_words(int f, char **a, int b);
void delete(Word **hashtable, int size);
Word **resize(Word **hashtable, int size);

Word **make_table(int size)
{
	int i = 0;
	Word **newtable =  malloc(size *sizeof(Word));
	for(i = 0; i < newSize; i++)
        {
                newtable[i] = NULL;
        }
}

void hash_words(int filename, char **argv, int argc)
{
	FILE *fp;
	char *token;
	char str[100];
	
	while(filename < argc)
	{
		fp = fopen(argv[filename], "r");
	
		if(fp == NULL)
		{
			fprintf(stderr, "ERROR");
		}
	
		while(fgets (str, 100, fp) != NULL)
		{
			token = strtok(str, " \n");
			while( token != NULL ) {
		/*		hashtable[hash_code(token)] = hash_node(token);				
		*/		token = strtok(NULL, " \n");
			}
		}
		fclose(fp);
		filename++;
		
	}
}


int hash_code(char *s)
{
	int hashval;

	for(hashval = 0; *s != '\0'; s++)
	{
		hashval = *s + 31 * hashval;
	}
	return hashval % hashsize;

}   

int get_index(int hashval)
{
	/*int index = hashval;
	int squared = 1;
	if(index > size - (squared ^2))
	{
		rehash*/
}




int main(int argc, char **argv)
{
	int wordnum = 10;	
	int filenames = 0;
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
}

	
/* Resize function for the hashtable.
 * 1) Calculate new table size.
 * 2) Create new hashtable.
 * 3) Rehash the words from the old table.
 * 4) Handle collisions.
 * 5) Free old table.
 * 6) Return pointer to new hashtable.
 */


Word **resize(Word **hashtable, int size)
{
	int newSize = size * 2 + 1;
	int collision = 0;
	int i = 0;
	int oldsize = size;
	Word **newtable;
	unsigned int hash;
	newtable = malloc(newSize * sizeof(Word));
	for(i = 0; i < newSize; i++)
	{
		newtable[i] = NULL;
	}
	i = 0;
	while (size > 0)
	{
		size--;
		hash = hash_code(hashtable[size]->word);
		if (newtable[hash] == NULL)
		{
			*newtable[hash] = *hashtable[size];
		}
		else
		{
			i = 1;
			collision = 1;
			while (collision)
			{
				if(newtable[(hash + i*i) % newSize] == NULL)
				{
					*newtable[(hash + i*i) % newSize] = *hashtable[size];
					collision = 0;
				}
				i++;
			}

		}
	}
size = newSize;
delete(hashtable, oldsize);
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
