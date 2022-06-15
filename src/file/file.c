#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "hashtable/hashtable.h"

#include "file.h"

#define INPUT_FILES_PATH "../files/"


// Function prototype
void reformatString(char *dest, char *src);


bool readFilesNames(Hashtable *hashtable, char *input_filename)
{
    char filePath[strlen(INPUT_FILES_PATH) + strlen(input_filename) + 1];

    strcpy(filePath, INPUT_FILES_PATH);
    strcat(filePath, input_filename);

    FILE *file = fopen(filePath, "r");

    if (!file)
    {
        return false;
    }

    int numberOfFiles = 0;

    fscanf(file, "%d", &numberOfFiles);

    for (int i = 0; i < numberOfFiles; i++)
    {
        char filename[CHAR_MAX];

        fscanf(file, "%s", filename);
        if (!readFileIntoHashtable(hashtable, filename, i + 1))
        {
            printf("Could read file '%s'", filename);
        }
    }

    return true;
}


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


void reformatString(char *dest, char *src)
{
    for (; *src; src++)
    {
        if (!ispunct((unsigned char) *src))
        {
            *dest++ = (char) tolower((unsigned char) *src);
        }
    }

    *dest = '\0';
}