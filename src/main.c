#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error trying to insertIntoHashtable into the hashtable.\n\n"
#define INVALID_VALUE "\nInvalid value.\n\n"


// Function prototype.
void cleanStdin();

void printOperationOptions();

int getUserOperationOption(int *operationOption);

void freeStructs(Hashtable *hashtable, PATRICIA *tree);


/*
 *  Code's start point.
 */
int main(void)
{
    while (true)
    {
        int structOption = -1;

        printf("What structures do you wish to load? "
               "\nNotice that the hashtable structure requires 16gb of RAM for a million words."
               "\n[0] Hashtable"
               "\n[1] Patricia"
               "\n[2] Both");

        if (!scanf("%d", &structOption) || structOption < 0 || structOption > 2)
        {
            cleanStdin();
            continue;
        }

        if (structOption == 0)
        {
            printf("");

            Hashtable hashtable;
            initialiseHashtable(&hashtable, 100);

            int operationOption = -1;

            while (getUserOperationOption(&operationOption) != 1)
            {
                printf(INVALID_VALUE);
                cleanStdin();
            }
        }
        else if (structOption == 1)
        {
            printf("");

            PATRICIA tree;
            initialisePATRICIA(&tree);

            int operationOption = -1;

            while (getUserOperationOption(&operationOption) != 1)
            {
                printf(INVALID_VALUE);
                cleanStdin();
            }
        }
        else
        {
            printf("");

            Hashtable hashtable;
            initialiseHashtable(&hashtable, 100);

            PATRICIA tree;
            initialisePATRICIA(&tree);

            int operationOption = -1;

            while (getUserOperationOption(&operationOption) != 1)
            {
                printf(INVALID_VALUE);
                cleanStdin();
            }
        }

        if (operationOption == 0)
        {
            printf("Leaving...\n");
            break;
        }

        // Initialise the hashtable.
        Hashtable hashtable;
        initialiseHashtable(&hashtable, 100); // You can change the hash table size.

        // Initialise the tree.
        PATRICIA tree;
        initialisePATRICIA(&tree);

        int numDocs = 0;

        char inputFilename[CHAR_MAX];
        printf("========================\n");
        printf("      Filename\n");
        printf("========================\n");
        scanf("%s", inputFilename);

        char **filenames = readFilenames(&hashtable, &tree, inputFilename, &numDocs);

        if (!filenames)
        {
            printf(FILE_ERROR, inputFilename);
            freeHashtable(&hashtable);
            cleanStdin();
            continue;
        }

        bool loop = true;

        while (loop)
        {
            if (operationOption == 1)
            {
                printf("Printing the tree\n");
                printTree(&tree);
                freeFilenames(filenames, numDocs);

//            printf("Printing the hashtable\n");
//            printHashtable(&hashtable);
//            freeFilenames(filenames, numDocs);
            }
            else if (operationOption == 2)
            {
                int numWords = 0;

                printf("Type the number of terms to look for:\n");
                if (!scanf("%d", &numWords) || numWords <= 0)
                {
                    printf(INVALID_VALUE);
                    freeFilenames(filenames, numDocs);
                    freeStructs(&hashtable, &tree);
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
            }
            else if (operationOption == 3)
            {
                printf("Printing the hashtable sorted\n");
                sortAndPrintHashtable(&hashtable);
                freeFilenames(filenames, numDocs);
            }

            loop = false;
        }

        freeStructs(&hashtable, &tree);
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


void printOperationOptions()
{
    printf("\nOptions"
           "\n[0] Exit"
           "\n[1] Print the inverted index"
           "\n[2] Search for a term"
           "\n[3] Print the inverted index - Ascending order"
           "\nChoose one of the options:\n");
}

int getUserOperationOption(int *operationOption)
{
    printOperationOptions();
    if (!scanf("%d", operationOption) || operationOption < 0 || operationOption > 4)
    {
        return -1;
    }

    return 1;
}


void freeStructs(Hashtable *hashtable, PATRICIA *tree)
{
    freeHashtable(hashtable);
    freeTree(tree);
}