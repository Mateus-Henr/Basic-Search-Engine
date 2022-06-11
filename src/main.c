#include <stdio.h>
#include <limits.h>

#include "file/arquivo.h"

#define FILE_ERROR "\nCouldn't open the file: '%s'.\n"

void cleanStdin();


int main(void)
{
    bool loop = true;

    while (loop)
    {
        char input_filename[CHAR_MAX];

        printf("Digite o nome do %s° arquivo: ", input_filename);
        if (readFile(input_filename))
        {
            printf(FILE_ERROR, input_filename);
            cleanStdin();
            continue;
        }

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