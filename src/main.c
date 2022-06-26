#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error trying to insertIntoHashtable into the hashtable.\n\n"
#define INVALID_VALUE "\nInvalid value.\n\n"


// Function prototypes.

bool getUserOperationOption(char *currStruct, char *filename, int *operationOption);

bool getNumberTerms(int *numTerms);

double calculateTotalTime(double initialTime);

void freeWords(char **words, int numWords);

void cleanStdin();


typedef enum
{
    Leave, Hash, Patricia, Both
} Structs;


typedef enum
{
    Exit, Print, Search
} Operations;


/*
 *  Code's start point.
 */
int main(void)
{
    while (true)
    {
        int structOption = -1;

        printf("\n\nStructures"
               "\nNotice that the hashtable you can edit the suggestion size in the code in the main code."
               "\n[0] Leave"
               "\n[1] Hashtable"
               "\n[2] Patricia"
               "\n[3] Both"
               "\nWhat structure(s) do you wish to load?\n");

        if (!scanf("%d", &structOption) || structOption < Leave || structOption > Both)
        {
            printf(INVALID_VALUE);
            cleanStdin();
            continue;
        }

        if (structOption == Leave)
        {
            printf("Bye :(\n");
            break;
        }
        else if (structOption == Hash)
        {
            printf("========================"
                   "\n      Filename"
                   "\n========================\n");

            char inputFilename[CHAR_MAX];
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

            printf("\nHashtable's size = %ld bytes\n", getSizeOfHashtable(&hashtable));
            printf("Total time hashtable = %lfs\n", calculateTotalTime(timeHashtable));

            while (true)
            {
                int operationOption = -1;

                while (!getUserOperationOption("hashtable", inputFilename, &operationOption))
                {
                    printf(INVALID_VALUE);
                    cleanStdin();
                }

                if (operationOption == Exit)
                {
                    printf("Leaving to main menu...\n");
                    break;
                }
                else if (operationOption == Print)
                {
                    printf("Printing hashtable inverted index");
                    sortAndPrintHashtable(&hashtable);
                }
                else if (operationOption == Search)
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
                    freeWords(words, numTerms);
                }
            }

            freeHashtable(&hashtable);
            freeFilenames(filenames, numFiles);
        }
        else if (structOption == Patricia)
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

            printf("\nPATRICIA's size = %ld bytes\n", getSizeOfPATRICIA(&tree));
            printf("Total time PATRICIA = %lfs\n", calculateTotalTime(timePATRICIA));

            while (true)
            {
                int operationOption = -1;

                while (!getUserOperationOption("PATRICIA", inputFilename, &operationOption))
                {
                    printf(INVALID_VALUE);
                    cleanStdin();
                }

                if (operationOption == Exit)
                {
                    printf("Leaving to main menu...\n");
                    break;
                }
                else if (operationOption == Print)
                {
                    printf("Printing PATRICIA inverted index");
                    printTree(&tree);
                }
                else if (operationOption == Search)
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

                    relevancePATRICIA(&tree, words, filenames, numTerms, numFiles);
                    freeWords(words, numTerms);
                }
            }

            freeTree(&tree);
            freeFilenames(filenames, numFiles);
        }
        else if (structOption == Both)
        {
            printf("========================"
                   "\n      Filename"
                   "\n========================\n");

            char inputFilename[CHAR_MAX];
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

            int numFilesPATRICIA = 0;
            readFilenamesPatricia(&tree, inputFilename, &numFilesPATRICIA);

            timePATRICIA = calculateTotalTime(timePATRICIA);
            ///-------------------------------------------------------------------------
            printf("\nHashtable's size = %ld bytes | PATRICIA's size = %ld bytes\n",
                   getSizeOfHashtable(&hashtable),
                   getSizeOfPATRICIA(&tree));
            printf("Total time hashtable = %lfs | Total time PATRICIA = %lfs\n", timeHashtable, timePATRICIA);

            while (true)
            {
                int operationOption = -1;

                while (!getUserOperationOption("hashtable and PATRICIA", inputFilename, &operationOption))
                {
                    printf(INVALID_VALUE);
                    cleanStdin();
                }

                if (operationOption == Exit)
                {
                    printf("Leaving to main menu...\n");
                    break;
                }
                else if (operationOption == Print)
                {
                    printf("Printing hashtable inverted index");
                    sortAndPrintHashtable(&hashtable);

                    printf("\nPrinting PATRICIA inverted index");
                    printTree(&tree);
                }
                else if (operationOption == Search)
                {
                    int numTerms = -1;

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
                    relevancePATRICIA(&tree, words, filenames, numTerms, numFiles);
                    freeWords(words, numTerms);
                }
            }

            freeHashtable(&hashtable);
            freeTree(&tree);
            freeFilenames(filenames, numFiles);
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


/*
 *  Gets the input from the user for the operation to be performed.
 *
 *  @param     currStruct          struct for operations.
 *  @param     filename            name of the file for operations.
 *  @param     operationOption     pointer to an int to receive the input.
 *  @return                        whether the operation was valid or not.
 */
bool getUserOperationOption(char *currStruct, char *filename, int *operationOption)
{
    printf("\n\nOptions on %s ('%s')"
           "\n[0] Exit to struct menu"
           "\n[1] Print inverted index"
           "\n[2] Search for a term"
           "\nChoose one of the options:\n", currStruct, filename);

    return scanf("%d", operationOption) && *operationOption >= Exit && *operationOption <= Search;
}


/*
 *  Gets the input from the user regarding the number of terms to be inputted.
 *
 *  @param     numTerms     pointer to an int to receive the input.
 *  @return                        whether the operation was valid or not.
 */
bool getNumberTerms(int *numTerms)
{
    printf("Type the number of terms:\n");

    return scanf("%d", numTerms) && *numTerms > 0;
}


/*
 *  Calculates total time based on a given initial time.
 *
 *  @param     initialTime     initial time.
 *  @return                    total time.
 */
double calculateTotalTime(double initialTime)
{
    return (clock() - initialTime) / CLOCKS_PER_SEC;
}


/*
 *  Deallocates array of strings containing words from memory.
 *
 *  @param     words        pointer to array containing filenames.
 *  @param     numWords     number of words in the array.
 */
void freeWords(char **words, int numWords)
{
    if (words)
    {
        for (int i = 0; i < numWords; ++i)
        {
            free(words[i]);
        }

        free(words);
    }
}