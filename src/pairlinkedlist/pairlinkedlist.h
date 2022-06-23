#include <stdbool.h>

#include "pairnode.h"
#include "tfidf/tfidf.h"

typedef struct
{
    PairNode *head;
    PairNode *tail;
    int size;
} PairLinkedList;

PairLinkedList *initialisePairLinkedList();

bool pushPair(PairLinkedList *list, long documentID);

PairNode *searchPairNode(PairLinkedList *list, long documentID);

int getPairLinkedListSize(PairLinkedList *list);

bool isPairLinkedListEmpty(PairLinkedList *list);

void getTFIDFPairLinkedList(PairLinkedList *list, TFIDF *tfidf, bool isRightWord);

void printPairLinkedList(PairLinkedList *list);

void freePairLinkedList(PairLinkedList *list);