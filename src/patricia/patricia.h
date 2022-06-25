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

void freeTree(PATRICIA *patricia);