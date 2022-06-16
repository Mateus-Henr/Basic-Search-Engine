#include "pairlinkedlist/pairlinkedlist.h"

typedef struct Node
{
    char *word;
    PairLinkedList *pairSet;
    struct Node *next;
} Node;

struct Node *initialiseNode(const char *word, long documentID);

struct Node *initialiseNodeWithExistentData(struct Node *node);

struct Node *searchNode(struct Node *head, const char *word);

void printNodes(struct Node *head);

int hashCode(const char *word, const int *weights);