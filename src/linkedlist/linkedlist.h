#include <stdbool.h>
#include "node.h"

typedef struct
{
    Node *head;
    Node *tail;
    unsigned int size;
} LinkedList;

LinkedList *initialiseLinkedList();

bool push(LinkedList *list, const char *word, long documentID);

bool removeFromList(LinkedList *list, const char *word);

unsigned int getSize(LinkedList *list);

bool isLinkedListEmpty(LinkedList *list);

void printLinkedList(LinkedList *list);