#include "pairlinkedlist/pairlinkedlist.h"

typedef struct Node
{
    char *word;
    PairLinkedList *pairSet;
    struct Node *next;
} Node;

struct Node *initialiseNode(const char *word, long documentID);

struct Node *initialiseNodeWithExistentData(struct Node *node);

int compareAlphabetically(const char *word, const char *anotherWord);

int hashCode(const char *word, const int *weights);