#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "file.h"

#define INPUT_FILES_PATH "../files/"
#define FILE_ERROR "\nCouldn't open the file: '%s'\n\n"


/*
 *  Reads filenames that contain input texts.
 *
 *  @param     hashtable         struct to Hashtable struct.
 *  @param     inputFilename     input filename.
 *  @param     numFiles          number of file.
 *  @return                      array with all the filenames.
 */
char **readFilenames(Hashtable *hashtable, PATRICIA *tree, char *inputFilename, int *numFiles)
{
    char filePath[strlen(INPUT_FILES_PATH) + strlen(inputFilename) + 1];

    strcpy(filePath, INPUT_FILES_PATH);
    strcat(filePath, inputFilename);

    FILE *file = fopen(filePath, "r");

    if (!file)
    {
        return NULL;
    }

    if (!fscanf(file, "%d", numFiles) || *numFiles <= 0)
    {
        return NULL;
    }

    char **filenames = (char **) malloc(*numFiles * sizeof(char *));

    for (int i = 0; i < *numFiles; i++)
    {
        char filename[CHAR_MAX];

        fscanf(file, "%s", filename);
        if (!readFileIntoStructs(hashtable, tree, filename, i + 1))
        {
            printf(FILE_ERROR, filename);
        }

        filenames[i] = (char *) malloc(strlen(filename) + 1);
        strcpy(filenames[i], filename);
    }

    fclose(file);
    file = NULL;

    return filenames;
}


/*
 *  Read text from file into the Patricia tree.
 *
 *  @param     hashtable      pointer to Hashtable struct.
 *  @param     tree           pointer to PATRICIA struct.
 *  @param     filename       filename that contains the text.
 *  @param     fileNumber     number of the file being read.
 *
 *  @return                  whether the operation was successful or not.
 */
bool readFileIntoStructs(Hashtable *hashtable, PATRICIA *tree, char *filename, int fileNumber)
{
    char filePath[strlen(INPUT_FILES_PATH) + strlen(filename) + 1];

    strcpy(filePath, INPUT_FILES_PATH);
    strcat(filePath, filename);

    FILE *file = fopen(filePath, "r");

    if (!file)
    {
        return false;
    }

    char string[CHAR_MAX];

    while (fscanf(file, "%s", string) != EOF)
    {
        char reformattedString[strlen(string) + 1];
        reformatString(reformattedString, string);

        if (strlen(reformattedString) != 0)
        {
            if (!insertIntoHashtable(hashtable, reformattedString, fileNumber))
            {
                return false;
            }

            if (!insertIntoTree(tree, reformattedString, fileNumber))
            {
                return false;
            }
        }
    }

    fclose(file);
    file = NULL;

    return true;
}


/*
 *  Reformats string by removing punctuation and spaces, and converts everything to lowercase.
 *  to lower case.
 *
 *  @param     dest     destination string.
 *  @param     src      source string.
 */
void reformatString(char *dest, char *src)
{
    while (*src)
    {
        if (isalpha((unsigned char) *src))
        {
            *dest++ = (char) tolower((unsigned char) *src);
        }

        src++;
    }

    *dest = '\0';
}


/*
 *  Deallocates filenames array from memory.
 *  Note: This is only used when the user enters an invalid value as
 *        some sort of "clean up" to allow the user to reenter a value.
 *
 *  @param     filenames     pointer to array of filenames.
 *  @param     n             size of the array.
 */
void freeFilenames(char **filenames, int n)
{
    if (filenames)
    {
        for (int i = 0; i < n; i++)
        {
            if (filenames[i])
            {
                free(filenames[i]);
            }
        }

        free(filenames);
    }
}