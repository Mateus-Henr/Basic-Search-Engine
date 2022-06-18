#include <stdbool.h>
#include "hashtable/hashtable.h"

void reformatString(char *dest, char *src);

char **readFilenames(Hashtable *hashtable, char *inputFilename, int *numFiles);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);

void freeFilenames(char **filenames, int n);