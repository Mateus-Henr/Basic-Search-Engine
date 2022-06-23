#include <stdbool.h>
#include "patricia/patricia.h"
//#include "hashtable/hashtable.h"

void reformatString(char *dest, char *src);

//char **readFilenames(Hashtable *hashtable, char *inputFilename, int *numFiles);

char **readFilenamesPatricia(PATRICIA *tree, char *inputFilename, int *numFiles);

//bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);

bool readFileIntoPatricia(PATRICIA *tree, char *filename, int fileNumber);

void freeFilenames(char **filenames, int n);