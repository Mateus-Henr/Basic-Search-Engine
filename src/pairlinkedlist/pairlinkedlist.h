#include <stdbool.h>
#include "pairnode.h"

typedef struct
{
    PairNode *head;
    PairNode *tail;
    int size;
} PairLinkedList;

PairLinkedList *initialisePairLinkedList();

bool pushPair(PairLinkedList *list, long documentID);

bool isPairLinkedListEmpty(PairLinkedList *list);

void printPairLinkedList(PairLinkedList *list);