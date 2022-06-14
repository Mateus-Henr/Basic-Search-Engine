#include <stdio.h>

#include "file.h"

bool readFile(char *filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        return false;
    }

    return true;
}