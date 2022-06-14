#include <stdbool.h>

typedef struct PairNode
{
    long numberOfOccurrences;
    long documentID;
    struct PairNode *next;
} PairNode;