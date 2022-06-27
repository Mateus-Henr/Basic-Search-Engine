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

    if (!list)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}


/*
 *  Searches pair node in the pair linked list.
 *
 *  @param     list           pointer to PairLinkedList struct.
 *  @param     documentID     id of the document to look for.
 */
PairNode *searchPairNode(PairLinkedList *list, long documentID)
{
    if (isPairLinkedListEmpty(list))
    {
        return NULL;
    }

    PairNode *pairNode = list->head;

    while (pairNode && pairNode->documentID != documentID)
    {
        pairNode = pairNode->next;
    }

    return pairNode;
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

    return true;
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
 *  Prints each externalNode of the pair linked list out.
 *
 *  @param     list     pointer to PairLinkedList struct.
 */
void printPairLinkedList(PairLinkedList *list)
{
    if (isPairLinkedListEmpty(list))
    {
        printf("\nEMPTY.\n");
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
 *  Calculates TF-IDF and put result into TFIDF struct.
 *
 *  @param     list      pointer to LinkedList struct.
 *  @param     tfidf     pointer to TFIDF struct.
 */
void getTFIDFPairLinkedList(PairLinkedList *list, TFIDF *tfidf, bool isRightWord)
{
    struct PairNode *currNode = list->head;

    while (currNode)
    {
        if (isRightWord)
        {
            bool hasBeenVisited = true;

            if (tfidf->occurrencesInDocs[currNode->documentID - 1] == 0)
            {
                hasBeenVisited = false;
            }

            tfidf->occurrencesInDocs[currNode->documentID - 1] += currNode->numberOfOccurrences;

            if (tfidf->occurrencesInDocs[currNode->documentID - 1] != 0 && !hasBeenVisited)
            {
                tfidf->DocsWithTerm++;
            }
        }

        tfidf->distinctTermsInDocs[currNode->documentID - 1]++;

        currNode = currNode->next;
    }
}


/*
 *  Gets the size of a PairLinkedList.
 *
 *  @param     list    pointer to PairLinkedList struct.
 *  @return            size of the pair linked list in bytes.
 */
long getSizeOfPairLinkedList(PairLinkedList *list)
{
    long size = 0;
    struct PairNode *currPairNode = list->head;

    while (currPairNode)
    {
        size += sizeof(PairNode);

        currPairNode = currPairNode->next;
    }

    size += sizeof(PairLinkedList);

    return size;
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

    free(list);
}