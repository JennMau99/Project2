#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"
#include <ctype.h>

int hash_words_helper(char *buffer, int strlength)
{
	unsigned int index;
	buffer[strlength] = '\0';
	index = get_index(hash_code(buffer), buffer, 1);
	if (hashtable[index] == NULL)
	{
		hashtable[index] = hash_node(buffer, 1);
		return 1; /*tableitems++*/
	}
	else
		hashtable[index]->frequency++;
		return 0;
}

void separate_by_words(FILE *fp)
{
	char ch;
	char *buffer;
	int buffermax = 10;
	int strlength = 0;
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
		if (isalpha(ch))
		{	
			ch = (char)tolower(ch);
			buffer[strlength] = ch;
			strlength++;
		}
		else if (strlength != 0)
		{
			tableitems = tableitems + hash_words_helper(buffer, strlength);
			
			free(buffer);
			buffermax = 10;
			strlength = 0;
			buffer = (char *) malloc(sizeof(char) * buffermax);
		}
		
		ch = getc(fp);
	}
	free(buffer);
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
	int size = 2;
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
			separate_by_words(fp);
			fclose(fp);
		}
		filename++;
			
	}
}

