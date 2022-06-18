#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error tying to insert into the hashtable.\n\n"
#define INVALID_VALUE "\nInvalid value.\n\n"


// Function prototype.
void cleanStdin();


/*
 *  Code's start point.
 */
int main(void)
{
    while (true)
    {
        char inputFilename[CHAR_MAX];

        printf("Type the input filename:\n");
        scanf("%s", inputFilename);

        Hashtable hashtable;
        initialiseHashtable(&hashtable, 1500);

        int numDocs;

        char **filenames = readFilenames(&hashtable, inputFilename, &numDocs);

        if (!filenames)
        {
            printf(FILE_ERROR, inputFilename);
            freeHashtable(&hashtable);
            cleanStdin();
            continue;
        }

        int numWords = 0;

        printf("Type the number of terms to look for:\n");
        if (!scanf("%d", &numWords) || numWords <= 0)
        {
            printf(INVALID_VALUE);
            freeFilenames(filenames, numDocs);
            freeHashtable(&hashtable);
            cleanStdin();
            continue;
        }

        char *words[numWords];

        for (int i = 0; i < numWords; i++)
        {
            char word[CHAR_MAX];

            printf("Type the word:\n");
            scanf("%s", word);

            words[i] = (char *) malloc(strlen(word) + 1);
            reformatString(words[i], word);
        }

        calculateRelevance(&hashtable, words, filenames, numWords, numDocs);

//        printHashtable(&hashtable);
//        sortAndPrintHashtable(&hashtable);

        freeHashtable(&hashtable);

        break;
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