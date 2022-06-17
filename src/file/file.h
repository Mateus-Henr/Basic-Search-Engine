#include <stdbool.h>
#include "hashtable/hashtable.h"

int readFilenames(Hashtable *hashtable, char *inputFilename);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);