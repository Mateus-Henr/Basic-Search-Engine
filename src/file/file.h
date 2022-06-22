#include <stdbool.h>
#include "patricia/treenode.h"
#include "hashtable/hashtable.h"

void reformatString(char *dest, char *src);

char **readFilenames(Hashtable *hashtable, char *inputFilename, int *numFiles);

char **readFilenamesPatricia(TreeNodeType *tree, char *inputFilename, int *numFiles);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);

bool readFileIntoPatricia(TreeNodeType *tree, char *filename, int fileNumber);

void freeFilenames(char **filenames, int n);