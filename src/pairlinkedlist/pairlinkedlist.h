#include <stdbool.h>
#include "pairnode.h"

typedef struct
{
    PairNode *head;
    PairNode *tail;
    unsigned int size;
} PairLinkedList;

PairLinkedList *initialisePairLinkedList();

bool pushPair(PairLinkedList *list);

bool isPairLinkedListEmpty(PairLinkedList *list);

