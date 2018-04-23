/* Resize function for the hashtable.
 * 1) Calculate new table size.
 * 2) Create new hashtable.
 * 3) Rehash the words from the old table.
 * 4) Handle collisions.
 * 5) Free old table.
 * 6) Return pointer to new hashtable.
 */

#include <stdlib.h>
#include "fw.h"

void delete(Word **hashtable, int size);

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
