/* Project 2: fw header */

#ifndef FW_H
#define FW_H


#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fw.h"
#include <ctype.h>


/*extern int size;*/

struct word{
	char *word;
	int frequency;
};


typedef struct word Word;

Word *hash_node(char *s, int freq);
unsigned int hash_code(char *s);
Word **make_table(int size);
void hash_words(int f, char **a, int b);
Word **resize(Word **hashtable);
int get_index(unsigned int hashval, char *s, int resize);
Word **sort(Word **hashtable);
int compare(const void *a, const void *b);
void print_table(int wordnum);


extern Word **hashtable;
extern int tablesize;
extern int tableitems;

#endif
