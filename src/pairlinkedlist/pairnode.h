#include <stdbool.h>

typedef struct PairNode
{
    long numberOfApearences;
    long idDocument;
    struct PairNode *next;
} PairNode;