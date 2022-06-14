#include "pairlinkedlist/pairlinkedlist.h"

typedef struct Node
{
    char *word;
    PairLinkedList *pairSet;
    struct Node *next;
} Node;

struct Node *initialiseNode(const char *word, long documentID);

int hashCode(const char *word);