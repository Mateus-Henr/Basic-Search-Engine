#include <stdbool.h>
#include "node.h"

typedef struct
{
    Node *head;
    Node *tail;
    unsigned int size;
} LinkedList;

void initialiseLinkedList(LinkedList *list);

bool push(LinkedList *list, char *word);

bool remove(LinkedList *list, char *word);

unsigned int getSize(LinkedList *list);

bool isEmpty(LinkedList *list);