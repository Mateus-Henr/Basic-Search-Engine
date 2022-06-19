#include <stdbool.h>
#include "treenode.h"

typedef struct
{
    TreeNodeType *root;
    int size;
} PATRICIA;

void initialisePATRICIA(PATRICIA *patricia);

bool insertIntoTree(PATRICIA *patricia, const char *word);

bool search(PATRICIA *patricia, const char *word);

int getTreeSize(PATRICIA *patricia);