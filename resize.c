/* Resize function for the hashtable.
 * 1) Calculate new table size.
 * 2) Create new hashtable.
 * 3) Rehash the words from the old table.
 * 4) Handle collisions.
 * 5) Free old table.
 * 6) Return pointer to new hashtable.
 */

Word *resize(Word *hashtable, int size)
{
	int newSize = size * 2 + 1;
	int collision = 0;
	int i = 0;
	Word *newtable[newSize] = {NULL};
	while (size > 0)
	{
		size--;
		unsigned int hash = hash_code(hashtable[size]->word);
		if (newtable[hash] == NULL)
		{
			newtable[hash] = *hashtable[size];
		}
		else
		{
			i = 1;
			collision = 1;
			while (collision)
			{
				if((hash + i*i) % newSize == NULL)
				{
					newtable[(hash + i*i) % newSize] = *hashtable[size];
					collision = 0;
				}
				i++;
			}
		}
	}
free(hashtable);
return newtable;
}
