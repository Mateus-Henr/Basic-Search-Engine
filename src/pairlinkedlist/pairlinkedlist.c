#include <stdlib.h>
#include <stddef.h>

#include "pairlinkedlist.h"

PairLinkedList *initialisePairLinkedList()
{
    PairLinkedList *list = (PairLinkedList *) malloc(sizeof(PairLinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

bool pushPair(PairLinkedList *list)
{
    struct PairNode *node = (PairNode *) malloc(sizeof(PairNode));

    if (!node)
    {
        return false;
    }

    if (!list->tail)
    {
        list->tail = node;
        list->head = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    return true;
}

bool isPairLinkedListEmpty(PairLinkedList *list)
{
    return list->head == NULL;
}
