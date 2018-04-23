/* Project 2: fw header */

#ifndef FW_H
#define FW_H

extern int size;

struct word{
	char *word;
	int frequency;
};

typedef struct word Word;

Word **resize(Word **hashtable, int size);
void delte(Word **hashtable, int size);

#endif
