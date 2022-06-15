#include <stdio.h>
#include <limits.h>
#include "hashtable/hashtable.h"
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error tying to insert into the hashtable.\n\n"
#define INVALID_VALUE "\nInvalid value.\n\n"


// Function prototype
void cleanStdin();


int main(void)
{
    bool loop = true;

    while (loop)
    {
        int numberOfFiles = 0;

        printf("Type the number of files:");
        if (!scanf("%d", &numberOfFiles) || numberOfFiles <= 0)
        {
            printf(INVALID_VALUE);
            cleanStdin();
            continue;
        }

        int currFile = 0;
        Hashtable hashtable;
        initialiseHashtable(&hashtable, 10);

        while (currFile < numberOfFiles)
        {
            char input_filename[CHAR_MAX];

            printf("Type the %d° input filename:", currFile + 1);
            scanf("%s", input_filename);

            if (!readFileIntoHashtable(&hashtable, input_filename, currFile + 1))
            {
                printf(FILE_ERROR, input_filename);
                cleanStdin();
                continue;
            }

            currFile++;
        }

        printHashtable(&hashtable);
        freeMemory(&hashtable);
        loop = false;
    }

    return 0;
}


void cleanStdin(void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}