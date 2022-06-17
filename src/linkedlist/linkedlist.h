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

bool pushSorted(LinkedList *list, Node *node);

int getLinkedListSize(LinkedList *list);

bool isLinkedListEmpty(LinkedList *list);

void getTermFrequencyInLinkedList(LinkedList *list, TFIDF *tfidf);

void printLinkedList(LinkedList *list);

void freeLinkedList(LinkedList *list);

void freeSortedLinkedList(LinkedList *list);