#include <stdio.h>
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
    struct PairNode *node = initialisePairNode(documentID);

    if (!node)
    {
        return false;
    }

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


int getPairLinkedListSize(PairLinkedList *list)
{
    return list->size;
}


bool isPairLinkedListEmpty(PairLinkedList *list)
{
    return list->head == NULL;
}


void printPairLinkedList(PairLinkedList *list)
{
    if (isPairLinkedListEmpty(list))
    {
        printf("EMPTY.\n");
        return;
    }

    struct PairNode *currNode = list->head;

    while (currNode)
    {
        printf("| <N = %ld | ID = %ld> ", currNode->numberOfOccurrences, currNode->documentID);
        currNode = currNode->next;
    }
}