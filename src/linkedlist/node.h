#include "pairlinkedlist/pairlinkedlist.h"

#include "linkedlist.h"

typedef struct Node
{
    char *word;
    PairLinkedList *pairSet;
    struct Node *next;
} Node;