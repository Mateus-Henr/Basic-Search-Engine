#include <stdio.h>
#include <limits.h>
#include "hashtable/hashtable.h"
#include "file/file.h"

#define FILE_ERROR "\nCouldn't open the file: '%s' or error tying to insert into the hashtable.\n\n"


// Function prototype.
void cleanStdin();


/*
 *  Code's start point.
 */
int main(void)
{
    bool loop = true;

    while (loop)
    {
        char input_filename[CHAR_MAX];

        printf("Type the input filename:");
        scanf("%s", input_filename);

        Hashtable hashtable;
        initialiseHashtable(&hashtable, 128);

        if (!readFilenames(&hashtable, input_filename))
        {
            printf(FILE_ERROR, input_filename);
            cleanStdin();
            continue;
        }

        printHashtable(&hashtable);
//        sortAndPrintHashtable(&hashtable);

        freeMemory(&hashtable);
        loop = false;
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