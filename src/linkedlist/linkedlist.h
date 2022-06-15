#include <stdbool.h>
#include "node.h"

typedef struct
{
    Node *head;
    Node *tail;
    int size;
} LinkedList;

LinkedList *initialiseLinkedList();

bool push(LinkedList *list, const char *word, long documentID);

int getLinkedListSize(LinkedList *list);

bool isLinkedListEmpty(LinkedList *list);

void printLinkedList(LinkedList *list);