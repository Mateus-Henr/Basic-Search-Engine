#include <stdbool.h>
#include "patricia/patricia.h"
#include "hashtable/hashtable.h"

char **readFilenamesHashtable(Hashtable *hashtable, char *inputFilename, int *numFiles);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);

char **readFilenamesPatricia(PATRICIA *tree, char *inputFilename, int *numFiles);

bool readFileIntoPatricia(PATRICIA *tree, char *filename, int fileNumber);

void reformatString(char *dest, char *src);

void freeFilenames(char **filenames, int numFiles);