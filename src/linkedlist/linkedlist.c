#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "linkedlist.h"

struct Node *searchNode(Node *head, const char *word, long documentID);

void initialiseLinkedList(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

bool push(LinkedList *list, const char *word, long documentID)
{
    struct Node *foundNode = searchNode(list->head, word, documentID);

    if (!foundNode)
    {
        struct Node *nodeToAdd = (Node *) malloc(sizeof(Node));

        if (!nodeToAdd)
        {
            return false;
        }

        list->tail->next = nodeToAdd;

        list->tail->next->pairSet = initialisePairLinkedList();

        if (!list->tail->next->pairSet)
        {
            return false;
        }

        pushPair(list->tail->next->pairSet, documentID);
    }
    else
    {
        struct PairNode *nodeToSearch = foundNode->pairSet->head;

        while (nodeToSearch && nodeToSearch->documentID == documentID)
        {
            nodeToSearch = nodeToSearch->next;
        }

        if (!nodeToSearch)
        {
            pushPair(foundNode->pairSet, documentID);
        }
        else
        {
            nodeToSearch->numberOfOccurrences = nodeToSearch->numberOfOccurrences + 1;
        }
    }

    return true;
}

bool removeFromList(LinkedList *list, char *word)
{

}

struct Node *searchNode(Node *head, const char *word, long documentID)
{
    while (head && strcmp(word, head->word) == 0)
    {
        head = head->next;
    }

    return head;
}

unsigned int getSize(LinkedList *list)
{
    return list->size;
}

bool isEmpty(LinkedList *list)
{
    return list->head == NULL;
}