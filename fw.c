#include <stdlib.h>
#include <stdio.h>
#include <string.h>



struct word {
        char *word;
        int frequency;
};

typedef struct word Word;

static Word *hashtable[100];

int main(int argc, char **argv)
{
        int wordnum = 10;
        int filenames = 0;
        if(argc > 1 && strcmp(argv[1], "-n"))
        {
                wordnum = argv[2][0];
                if(argc > 2)
                {
                        filenames = 2;
                }
        }
        else if(argc > 0)
        {
                filenames = 1;
        }

}

void hash_words(int filenames, char **argv)
{


/* what's up fam it's your girl richa!*/
