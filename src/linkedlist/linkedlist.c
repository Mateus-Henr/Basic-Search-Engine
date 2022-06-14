#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "node.h"
#include "pairlinkedlist/pairlinkedlist.h"

#include "linkedlist.h"

struct Node *searchNodeOrLastElement(Node *head, char *word);

void initialiseLinkedList(LinkedList *list)
{
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

bool push(LinkedList *list, char *word)
{
    struct Node *foundNode = searchNodeOrLastElement(list->head, word);

    if (!foundNode)
    {
        struct Node *nodeToadd = (Node *) malloc(sizeof(Node));
        list->tail->next = nodeToadd;

        list->tail->next->pairSet = initialisePairLinkedList();
    }
}

bool remove(LinkedList *list, char *word)
{

}

struct Node *searchNodeOrLastElement(Node *head, char *word)
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