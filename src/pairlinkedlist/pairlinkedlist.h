#include <stdbool.h>


#ifndef _PAIR_LINKED_LIST_H_
#define _PAIR_LINKED_LIST_H_

#include "pairnode.h"
#include "tfidf/tfidf.h"
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