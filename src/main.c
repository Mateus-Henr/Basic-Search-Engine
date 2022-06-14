#include <stdio.h>
#include <limits.h>
#include "hashtable//hashtable.h"

#include "file/file.h"

#define INPUT_FILES_PATH "../"
#define FILE_ERROR "\nCouldn't open the file: '%s'.\n"

void cleanStdin();


int main(void)
{
//    bool loop = true;
//
//    while (loop)
//    {
//        char input_filename[CHAR_MAX];
//
//        printf("Type the input filename: ");
//        if (readFile(input_filename))
//        {
//            printf(FILE_ERROR, input_filename);
//            cleanStdin();
//            continue;
//        }
//
//        loop = false;
//    }

    Hashtable hashtable;

    initialiseHashtable(&hashtable, 10);
    insert(&hashtable, "Mateus", 10);

    printHashtable(&hashtable);

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