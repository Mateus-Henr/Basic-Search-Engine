#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "linkedlist.h"


// Function prototype
struct Node *searchNode(struct Node *head, const char *word);


/*
 *  Initialises LinkedList struct with default values.
 *
 *  @return         pointer for LinkedList struct dynamically allocated.
 */
LinkedList *initialiseLinkedList()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
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

    struct PairNode *nodeToSearch = foundNode->pairSet->head;

    while (nodeToSearch && nodeToSearch->documentID != documentID)
    {
        nodeToSearch = nodeToSearch->next;
    }

    if (!nodeToSearch)
    {
        return pushPair(foundNode->pairSet, documentID);
    }

    nodeToSearch->numberOfOccurrences++;

    return true;
}


/*
 *  Searches for a node in the linked list.
 *
 *  @param     list     pointer to LinkedList struct.
 *  @param     word     word to search for.
 *  @return             pointer for the node if found or null.
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
 *  Gets the linked list size.
 *
 *  @param     list     pointer to LinkedList struct.
 *  @return             the list size.
 */
int getLinkedListSize(LinkedList *list)
{
    return list->size;
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

    currNode = list->head;

    while (currNode)
    {
        struct Node *nodeToDelete = currNode;
        currNode = currNode->next;
        free(nodeToDelete);
    }
}