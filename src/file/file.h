#include <stdbool.h>
#include "hashtable/hashtable.h"

#define INPUT_FILES_PATH "../files/"

char **readFilenames(Hashtable *hashtable, char *inputFilename, int *numOfFiles);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);