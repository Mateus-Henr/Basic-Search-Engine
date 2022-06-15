#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include "hashtable/hashtable.h"

#include "file.h"

#define INPUT_FILES_PATH "../files/"

void reformatString(char *dest, char *src);

bool readFileIntoHashtable(Hashtable *hashtable, int number, char *filename)
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

        insert(hashtable, reformattedString, number);
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