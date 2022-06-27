#include <stdbool.h>
#include "treenode.h"

typedef struct
{
    TreeNodeType *root;
} PATRICIA;

void initialisePATRICIA(PATRICIA *patricia);

bool insertIntoTree(PATRICIA *patricia, char *word, int documentID);

void printTree(PATRICIA *patricia);

void getTFIDFPATRICIA(PATRICIA *patricia, TFIDF *tfidf);

void relevancePATRICIA(PATRICIA *tree, char **words, char **filenames, int numWords, int numDocs);

long getSizeOfPATRICIA(PATRICIA *patricia);

void freeTree(PATRICIA *patricia);