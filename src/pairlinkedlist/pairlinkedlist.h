#include <stdbool.h>


#ifndef _PAIR_LINKED_LIST_H_
#define _PAIR_LINKED_LIST_H_

#include "pairnode.h"
#include "tfidf/tfidf.h"

typedef struct
{
    PairNode *head;
    PairNode *tail;
} PairLinkedList;

PairLinkedList *initialisePairLinkedList(void);

PairNode *searchPairNode(PairLinkedList *list, long documentID);

bool pushPair(PairLinkedList *list, long documentID);

bool isPairLinkedListEmpty(PairLinkedList *list);

void printPairLinkedList(PairLinkedList *list);

void getTFIDFPairLinkedList(PairLinkedList *list, TFIDF *tfidf, bool isRightWord);

long getSizeOfPairLinkedList(PairLinkedList *list);

void freePairLinkedList(PairLinkedList *list);

#endif