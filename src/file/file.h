#include <stdbool.h>
#include "hashtable/hashtable.h"

char **readFilenames(Hashtable *hashtable, char *inputFilename, int *numFiles);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);