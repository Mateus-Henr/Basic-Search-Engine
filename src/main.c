#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error trying to insertIntoHashtable into the hashtable.\n\n"
#define INVALID_VALUE "\nInvalid value.\n\n"


// Function prototype.
void cleanStdin();

double calculateTotalTime(double initialTime);

bool getUserOperationOption(int *operationOption);

bool getNumberTerms(int *numTerms);


/*
 *  Code's start point.
 */
int main(void)
{
    while (true)
    {
        int structOption = -1;

        printf("\n\nStructures"
               "\nNotice that the hashtable structure requires 16gb of RAM for a million words."
               "\n[0] Hashtable"
               "\n[1] Patricia"
               "\n[2] Both"
               "\nWhat structure(s) do you wish to load?\n");

        if (!scanf("%d", &structOption) || structOption < 0 || structOption > 2)
        {
            cleanStdin();
            continue;
        }

        if (structOption == 0)
        {
            char inputFilename[CHAR_MAX];

            printf("========================"
                   "\n      Filename"
                   "\n========================\n");
            scanf("%s", inputFilename);

            double timeHashtable = clock();

            Hashtable hashtable;
            initialiseHashtable(&hashtable, 100);

            int numFiles = 0;
            char **filenames = readFilenamesHashtable(&hashtable, inputFilename, &numFiles);

            if (!filenames)
            {
                printf(FILE_ERROR, inputFilename);
                freeHashtable(&hashtable);
                cleanStdin();
                continue;
            }

            printf("\nTotal time hashtable = %lfs\n", calculateTotalTime(timeHashtable));

            int operationOption = -1;

            while (!getUserOperationOption(&operationOption))
            {
                printf(INVALID_VALUE);
                cleanStdin();
            }

            if (operationOption == 0)
            {
                printf("Leaving...\n");
                break;
            }
            else if (operationOption == 1)
            {
                printf("Printing hashtable inverted index");
                sortAndPrintHashtable(&hashtable);
            }
            else if (operationOption == 2)
            {
                int numTerms = 0;

                while (!getNumberTerms(&numTerms))
                {
                    printf(INVALID_VALUE);
                    cleanStdin();
                }

                char *words[numTerms];

                for (int i = 0; i < numTerms; i++)
                {
                    char word[CHAR_MAX];

                    printf("Type the word:\n");
                    scanf("%s", word);

                    words[i] = (char *) malloc(strlen(word) + 1);
                    reformatString(words[i], word);
                }

                relevanceHashtable(&hashtable, words, filenames, numTerms, numFiles);
            }

            freeHashtable(&hashtable);
        }
        else if (structOption == 1)
        {
            char inputFilename[CHAR_MAX];

            printf("========================"
                   "\n      Filename"
                   "\n========================\n");
            scanf("%s", inputFilename);

            double timePATRICIA = clock();

            PATRICIA tree;
            initialisePATRICIA(&tree);

            int numFiles = 0;
            char **filenames = readFilenamesPatricia(&tree, inputFilename, &numFiles);

            if (!filenames)
            {
                printf(FILE_ERROR, inputFilename);
                freeTree(&tree);
                cleanStdin();
                continue;
            }

            printf("\nTotal time PATRICIA = %lfs\n", calculateTotalTime(timePATRICIA));

            int operationOption = -1;

            while (!getUserOperationOption(&operationOption))
            {
                printf(INVALID_VALUE);
                cleanStdin();
            }

            if (operationOption == 0)
            {
                printf("Leaving...\n");
                break;
            }
            else if (operationOption == 1)
            {
                printf("Printing PATRICIA inverted index");
                printTree(&tree);
            }
            else if (operationOption == 2)
            {
                int numTerms = 0;

                while (!getNumberTerms(&numTerms))
                {
                    printf(INVALID_VALUE);
                    cleanStdin();
                }

                char *words[numTerms];

                for (int i = 0; i < numTerms; i++)
                {
                    char word[CHAR_MAX];

                    printf("Type the word:\n");
                    scanf("%s", word);

                    words[i] = (char *) malloc(strlen(word) + 1);
                    reformatString(words[i], word);
                }

//                relevancePATRICIA(&tree, words, filenames, numTerms, numFiles);
            }

            freeTree(&tree);
        }
        else
        {
            char inputFilename[CHAR_MAX];

            printf("========================"
                   "\n      Filename"
                   "\n========================\n");
            scanf("%s", inputFilename);

            double timeHashtable = clock();

            /// Hashtable
            Hashtable hashtable;
            initialiseHashtable(&hashtable, 100);

            int numFiles = 0;
            char **filenames = readFilenamesHashtable(&hashtable, inputFilename, &numFiles);

            if (!filenames)
            {
                printf(FILE_ERROR, inputFilename);
                freeHashtable(&hashtable);
                cleanStdin();
                continue;
            }

            timeHashtable = calculateTotalTime(timeHashtable);
            ///-------------------------------------------------------------------------


            /// PATRICIA
            double timePATRICIA = clock();

            PATRICIA tree;
            initialisePATRICIA(&tree);

            timePATRICIA = calculateTotalTime(timePATRICIA);

            int numFilesPATRICIA = 0;
            readFilenamesPatricia(&tree, inputFilename, &numFilesPATRICIA);
            ///-------------------------------------------------------------------------

            printf("\nTotal time hashtable = %lfs | Total time PATRICIA = %lfs\n", timeHashtable, timePATRICIA);

            int operationOption = -1;

            while (!getUserOperationOption(&operationOption))
            {
                printf(INVALID_VALUE);
                cleanStdin();
            }

            if (operationOption == 0)
            {
                printf("Leaving...\n");
                break;
            }
            else if (operationOption == 1)
            {
                printf("Printing hashtable inverted index");
                sortAndPrintHashtable(&hashtable);

                printf("\nPrinting PATRICIA inverted index");
                printTree(&tree);
            }
            else if (operationOption == 2)
            {
                int numTerms = 0;

                while (!getNumberTerms(&numTerms))
                {
                    printf(INVALID_VALUE);
                    cleanStdin();
                }

                char *words[numTerms];

                for (int i = 0; i < numTerms; i++)
                {
                    char word[CHAR_MAX];

                    printf("Type the word:\n");
                    scanf("%s", word);

                    words[i] = (char *) malloc(strlen(word) + 1);
                    reformatString(words[i], word);
                }

                relevanceHashtable(&hashtable, words, filenames, numTerms, numFiles);
                // relevancePATRICIA(&tree, words, filenames, numTerms, numFiles);
            }

            freeHashtable(&hashtable);
            freeTree(&tree);
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


bool getUserOperationOption(int *operationOption)
{
    printf("\nOptions"
           "\n[0] Exit"
           "\n[1] Print inverted index"
           "\n[2] Search for a term"
           "\nChoose one of the options:\n");

    return scanf("%d", operationOption) && *operationOption >= 0 && *operationOption <= 2;
}


bool getNumberTerms(int *numTerms)
{
    return scanf("%d", numTerms) && *numTerms > 0;
}


double calculateTotalTime(double initialTime)
{
    return (clock() - initialTime) / CLOCKS_PER_SEC;
}