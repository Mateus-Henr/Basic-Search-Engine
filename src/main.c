#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error trying to insert into the hashtable.\n\n"
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
        int option = 0;

        printf("\nChoose one of the option:\n");
        printf("[1] Print the inverted index\n");
        printf("[2] Search for a term\n");
        printf("[3] Print the inverted index - alphabetic order\n");
        printf("[0] Leave\n");

        if (!scanf("%d", &option))
        {
            printf("Insert a valid option (1,2 or 3)\n");
            cleanStdin();
            continue;
        }

        if (option == 0)
        {
            printf("Leaving...\n");
            break;
        }

        // Initialise the hashtable.
        Hashtable hashtable;
        initialiseHashtable(&hashtable, 1000); // You can change the hash table size

        int numDocs;

        char inputFilename[CHAR_MAX];
        printf("========================\n");
        printf("      Filename\n");
        printf("========================\n");
        scanf("%s", inputFilename);

        char **filenames = readFilenames(&hashtable, inputFilename, &numDocs);

        if (!filenames)
        {
            printf(FILE_ERROR, inputFilename);
            freeHashtable(&hashtable);
            cleanStdin();
            continue;
        }

        else if (option == 1)
        {

            printf("Printing the hashtable\n");
            printHashtable(&hashtable);
        }
        else if (option == 2)
        {
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

            freeHashtable(&hashtable);
        }

        else if (option == 3)
        {
            printf("Printing the hashtable sorted\n");
            sortAndPrintHashtable(&hashtable);
        }
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