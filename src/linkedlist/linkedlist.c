#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "linkedlist.h"


// Function prototype.

struct Node *searchNode(struct Node *head, const char *word);


/*
 *  Initialises LinkedList struct with default values.
 *
 *  @return         pointer for LinkedList struct dynamically allocated.
 */
LinkedList *initialiseLinkedList()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    if (!list)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;

    return list;
}


/*
 *  Searches for a externalNode in the linked list.
 *
 *  @param     list     pointer to LinkedList struct.
 *  @param     word     word to search for.
 *  @return             pointer for the externalNode if found or null.
 */
struct Node *searchNode(struct Node *head, const char *word)
{
    while (head && strcmp(word, head->word) != 0)
    {
        head = head->next;
    }

    return head;
}


/*
 *  Pushes a new word into the linked list.
 *
 *  @param     list           pointer to LinkedList struct.
 *  @param     word           word to be pushed.
 *  @param     documentID     document's number (ID).
 *  @return                   whether the operation was successful or not.
 */
bool push(LinkedList *list, const char *word, long documentID)
{
    if (isLinkedListEmpty(list))
    {
        list->head = initialiseNode(word, documentID);
        list->tail = list->head;

        return list->tail;
    }

    struct Node *foundNode = searchNode(list->head, word);

    if (!foundNode)
    {
        list->tail->next = initialiseNode(word, documentID);
        list->tail = list->tail->next;

        return list->tail;
    }

    struct PairNode *nodeToSearch = searchPairNode(foundNode->pairSet, documentID);

    if (!nodeToSearch)
    {
        return pushPair(foundNode->pairSet, documentID);
    }

    nodeToSearch->numberOfOccurrences++;

    return true;
}


/*
 *  Inserts data into a linked list in a sorted fashion.
 *  Note: This method is internally used to get data sorted.
 *
 *  @param     list     pointer to LinkedList struct.
 *  @param     externalNode     pointer to the externalNode to be added.
 */
bool pushSorted(LinkedList *list, Node *node)
{
    struct Node *nodeCopy = initialiseNodeWithExistentData(node);

    if (isLinkedListEmpty(list))
    {
        list->head = nodeCopy;
        list->tail = nodeCopy;

        return true;
    }

    if (compareAlphabetically(list->tail->word, nodeCopy->word) == -1)
    {
        list->tail->next = nodeCopy;
        list->tail = nodeCopy;
    }
    else if (compareAlphabetically(list->head->word, nodeCopy->word) == 1)
    {
        nodeCopy->next = list->head;
        list->head = nodeCopy;
    }
    else
    {
        struct Node *currNode = list->head;

        while (currNode->next && compareAlphabetically(currNode->next->word, nodeCopy->word) != 1)
        {
            currNode = currNode->next;
        }

        nodeCopy->next = currNode->next;
        currNode->next = nodeCopy;
    }

    return true;
}


/*
 *  Checks if the linked list is empty.
 *
 *  @param     list     pointer to LinkedList struct.
 *  @return             whether the linked list is empty or not.
 */
bool isLinkedListEmpty(LinkedList *list)
{
    return list->head == NULL;
}


/*
 *  Prints the linked list out.
 *
 *  @param     list     pointer to LinkedList struct.
 */
void printLinkedList(LinkedList *list)
{
    if (isLinkedListEmpty(list))
    {
        printf("EMPTY.\n");
        return;
    }

    struct Node *currNode = list->head;

    while (currNode)
    {
        printf("%s ", currNode->word);
        printPairLinkedList(currNode->pairSet);
        printf("\n");

        currNode = currNode->next;
    }

    printf("\n");
}


/*
 *  Calculates TF-IDF and put result into TFIDF struct.
 *
 *  @param     list      pointer to LinkedList struct.
 *  @param     tfidf     pointer to TFIDF struct.
 */
void getTFIDFLinkedList(LinkedList *list, TFIDF *tfidf)
{
    struct Node *currNode = list->head;

    while (currNode)
    {
        getTFIDFPairLinkedList(currNode->pairSet, tfidf, !strcmp(currNode->word, tfidf->word));

        currNode = currNode->next;
    }
}


/*
 *  Deallocates linked list and its content allocated dynamically from memory.
 *
 *  @param     list     pointer to LinkedList struct.
 */
void freeLinkedList(LinkedList *list)
{
    struct Node *currNode = list->head;

    while (currNode)
    {
        if (currNode->word)
        {
            free(currNode->word);
        }

        if (currNode->pairSet && currNode->pairSet->size > 0)
        {
            freePairLinkedList(currNode->pairSet);
        }

        struct Node *nodeToDelete = currNode;
        currNode = currNode->next;
        free(nodeToDelete);
    }

    free(list);
}


/*
 *  Deallocates struct that was built for sorted data.
 *  It only deallocates nodes from the struct Node.
 *  Note: This method is used only for the linked list that was allocated
 *        by the "sortAndPrintHashtable" method.
 *
 *  @param     list     pointer to LinkedList struct.
 */
void freeSortedLinkedList(LinkedList *list)
{
    struct Node *currNode = list->head;

    while (currNode)
    {
        struct Node *nodeToDelete = currNode;
        currNode = currNode->next;
        free(nodeToDelete);
    }

    free(list);
}