#include <stdbool.h>
#include "patricia/patricia.h"
#include "hashtable/hashtable.h"

void reformatString(char *dest, char *src);

char **readFilenames(Hashtable *hashtable, PATRICIA *tree, char *inputFilename, int *numFiles);

bool readFileIntoStructs(Hashtable *hashtable, PATRICIA *tree, char *filename, int fileNumber);

void freeFilenames(char **filenames, int n);