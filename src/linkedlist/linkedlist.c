#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "linkedlist.h"

struct Node *searchNode(struct Node *head, const char *word);

LinkedList *initialiseLinkedList()
{
    LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));

    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    return list;
}

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
        pushPair(foundNode->pairSet, documentID);
    }
    else
    {
        nodeToSearch->numberOfOccurrences++;
    }

    return true;
}

bool removeFromList(LinkedList *list, const char *word)
{
    return true;
}

struct Node *searchNode(struct Node *head, const char *word)
{
    while (head && strcmp(word, head->word) != 0)
    {
        head = head->next;
    }

    return head;
}

unsigned int getSize(LinkedList *list)
{
    return list->size;
}

bool isLinkedListEmpty(LinkedList *list)
{
    return list->head == NULL;
}

void printLinkedList(LinkedList *list)
{
    struct Node *currNode = list->head;

    while (currNode)
    {
        printf("%s => ", currNode->word);
        currNode = currNode->next;
    }

    printf("\n");
}