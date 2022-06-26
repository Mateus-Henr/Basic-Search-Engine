#include <stdbool.h>

#include "treenode.h"

typedef struct
{
    TreeNodeType *root;
    int size;
} PATRICIA;

void initialisePATRICIA(PATRICIA *patricia);

bool insertIntoTree(PATRICIA *patricia, char *word, int documentID);

void search(PATRICIA *patricia, char *word);

int getTreeSize(PATRICIA *patricia);

void printTree(PATRICIA *patricia);

void getTFIDFPATRICIA(PATRICIA *patricia, TFIDF *tfidf);

void freeTree(PATRICIA *patricia);

void relevancePATRICIA(PATRICIA *tree, char **words, char **filenames, int numWords, int numDocs);