#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "pairlinkedlist.h"


/*
 *  Initialises PairLinkedList with default values.
 *
 *  @return                 pointer to the initialised struct.
 */
PairLinkedList *initialisePairLinkedList()
{
    PairLinkedList *list = (PairLinkedList *) malloc(sizeof(PairLinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}


/*
 *  Pushes a new pair (PairNode) to the list.
 *
 *  @param     list           pointer to PairLinkedList struct.
 *  @param     documentID     document's number (ID).
 *  @return                   whether the operation was successful or not.
 */
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


/*
 *  Gets the pair linked list size.
 *
 *  @param     list     pointer to PairLinkedList struct.
 *  @return             list size.
 */
int getPairLinkedListSize(PairLinkedList *list)
{
    return list->size;
}


/*
 *  Checks whether the pair linked list is empty or not.
 *
 *  @param     list     pointer to PairLinkedList struct.
 *  @param              whether the list is empty or not.
 */
bool isPairLinkedListEmpty(PairLinkedList *list)
{
    return list->head == NULL;
}


/*
 *  Prints each node of the pair linked list out.
 *
 *  @param     list     pointer to PairLinkedList struct.
 */
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


/*
 *  Deallocates pair linked list allocated dynamically from memory.
 *
 *  @param     list     pointer to PairLinkedList struct.
 */
void freePairLinkedList(PairLinkedList *list)
{
    struct PairNode *currPairNode = list->head;

    while (currPairNode)
    {
        struct PairNode *pairNodeToDelete = currPairNode;
        currPairNode = currPairNode->next;
        free(pairNodeToDelete);
    }
}