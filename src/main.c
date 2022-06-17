#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error tying to insert into the hashtable.\n\n"


// Function prototype.
void cleanStdin();


/*
 *  Code's start point.
 */
int main(void)
{
    bool loop = true;

    while (loop)
    {
        char input_filename[CHAR_MAX];

        printf("Type the input filename:\n");
        scanf("%s", input_filename);

        Hashtable hashtable;
        initialiseHashtable(&hashtable, 128);

        int filesNumber = readFilenames(&hashtable, input_filename);

        if (filesNumber == -1)
        {
            printf(FILE_ERROR, input_filename);
            cleanStdin();
            continue;
        }

        int numWords = 0;

        printf("Type the number of terms to look for:\n");
        if (!scanf("%d", &numWords) || numWords <= 0)
        {
            cleanStdin();
            continue;
        }

        char **words = (char **) malloc(numWords * sizeof(char *));

        for (int i = 0; i < numWords; i++)
        {
            words[i] = (char *) malloc(CHAR_MAX);

            printf("Type the word:\n");
            scanf("%s", words[i]);
        }

        calculateRelevance(&hashtable, words, numWords, filesNumber);

//        printHashtable(&hashtable);
//        sortAndPrintHashtable(&hashtable);

        freeHashtable(&hashtable);
        loop = false;
    }

    return 0;
}


/*
 *  Clears stdin to avoid problems with the "scanf()" function.
 */
void cleanStdin(void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}