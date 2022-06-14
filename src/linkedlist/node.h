#include "pairlinkedlist/pairlinkedlist.h"

typedef struct Node
{
    char *word;
    PairLinkedList *pairSet;
    struct Node *next;
} Node;