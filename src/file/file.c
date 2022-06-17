#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "file.h"

#define INPUT_FILES_PATH "../files/"
#define FILE_ERROR "\nCouldn't open the file: '%s'\n\n"


// Function prototype.
void reformatString(char *dest, char *src);


/*
 *  Reads filenames that contain input texts.
 *
 *  @param     hashtable         struct to Hashtable struct.
 *  @param     inputFilename     input filename.
 *  @return                      whether the operation was successful or not.
 */
int readFilenames(Hashtable *hashtable, char *inputFilename)
{
    char filePath[strlen(INPUT_FILES_PATH) + strlen(inputFilename) + 1];

    strcpy(filePath, INPUT_FILES_PATH);
    strcat(filePath, inputFilename);

    FILE *file = fopen(filePath, "r");

    if (!file)
    {
        return -1;
    }

    int numberOfFiles = 0;

    if (!fscanf(file, "%d", &numberOfFiles))
    {
        return -1;
    }

    for (int i = 0; i < numberOfFiles; i++)
    {
        char filename[CHAR_MAX];

        fscanf(file, "%s", filename);
        if (!readFileIntoHashtable(hashtable, filename, i + 1))
        {
            printf(FILE_ERROR, filename);
        }
    }

    return numberOfFiles;
}


/*
 *  Read text from file into the hashtable.
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

    while (!feof(file))
    {
        char string[CHAR_MAX];
        fscanf(file, "%s", string);

        char reformattedString[strlen(string) + 1];
        reformatString(reformattedString, string);

        if (!insert(hashtable, reformattedString, fileNumber))
        {
            return false;
        }
    }

    return true;
}


/*
 *  Reformats string by removing punctuation and converting everything
 *  to lower case.
 *
 *  @param     dest     destination string.
 *  @param     src      source string.
 */
void reformatString(char *dest, char *src)
{
    while (*src)
    {
        if (!ispunct((unsigned char) *src))
        {
            *dest++ = (char) tolower((unsigned char) *src);
        }

        src++;
    }

    *dest = '\0';
}