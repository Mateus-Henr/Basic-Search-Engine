#include <stdbool.h>
#include "node.h"
/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

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

long getSizeOfLinkedList(LinkedList *list);