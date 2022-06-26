#include <stdbool.h>
#include "node.h"

typedef struct
{
    Node *head;
    Node *tail;
} LinkedList;

LinkedList *initialiseLinkedList();

bool push(LinkedList *list, const char *word, long documentID);

bool pushSorted(LinkedList *list, Node *node);

bool isLinkedListEmpty(LinkedList *list);

void printLinkedList(LinkedList *list);

void getTFIDFLinkedList(LinkedList *list, TFIDF *tfidf);

void freeLinkedList(LinkedList *list);

void freeSortedLinkedList(LinkedList *list);