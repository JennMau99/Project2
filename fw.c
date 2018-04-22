#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* #include "fw.h" */

#define hashsize 101

struct word {
	char *word;
	int frequency;
};

typedef struct word Word;

static Word hashtable[hashsize];

Word hash_node(char *s);
int hash_code(char *s);

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

	
