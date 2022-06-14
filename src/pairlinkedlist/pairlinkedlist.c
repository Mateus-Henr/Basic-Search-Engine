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

bool pushPair(PairLinkedList *list, long documentID)
{
    struct PairNode *node = (PairNode *) malloc(sizeof(PairNode));

    if (!node)
    {
        return false;
    }

    node->documentID = documentID;
    node->numberOfOccurrences = 1;
    node->next = NULL;

    if (isPairLinkedListEmpty(list))
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }

    list->size++;

    return true;
}

bool isPairLinkedListEmpty(PairLinkedList *list)
{
    return list->head == NULL;
}
