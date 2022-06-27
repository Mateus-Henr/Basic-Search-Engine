/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */
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
 *  @param     numFiles          pointer to int that stores the number of files.
 *  @return                      array with all the filenames.
 */
char **readFilenamesHashtable(Hashtable *hashtable, char *inputFilename, int *numFiles)
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
        if (!readFileIntoHashtable(hashtable, filename, i + 1))
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
 *  Reads text from file into the hashtable.
 *
 *  @param     hashtable     struct to Hashtable struct.
 *  @param     filename      filename that contains the text.
 *  @param     fileNumber    number of the file being read.
 *  @return                  whether the operation was successful or not.
 */
bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber)
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
        }
    }

    fclose(file);
    file = NULL;

    return true;
}


/*
 *  Reads filenames that contain input texts.
 *
 *  @param     hashtable         struct to Hashtable struct.
 *  @param     inputFilename     input filename.
 *  @param     numFiles          number of file.
 *  @return                      array with all the filenames.
 */
char **readFilenamesPatricia(PATRICIA *tree, char *inputFilename, int *numFiles)
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
        if (!readFileIntoPatricia(tree, filename, i + 1))
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


/* Reads text from file into the PATRICIA tree.
 *
 * @param   tree        struct for the patricia tree
 * @param   filename    filename that contains the text.
 * @param   fileNumber  number of the file being read.
 *
 * @return                  whether the operation was successful or not.
 */
bool readFileIntoPatricia(PATRICIA *tree, char *filename, int fileNumber)
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
 *  Deallocates array of strings containing filenames from memory.
 *
 *  @param     filenames     pointer to array containing filenames.
 *  @param     numFiles      number of files in the array.
 */
void freeFilenames(char **filenames, int numFiles)
{
    if (filenames)
    {
        for (int i = 0; i < numFiles; i++)
        {
            if (filenames[i])
            {
                free(filenames[i]);
            }
        }

        free(filenames);
    }
}