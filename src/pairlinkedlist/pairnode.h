typedef struct PairNode
{
    long numberOfOccurrences;
    long documentID;
    struct PairNode *next;
} PairNode;

PairNode *initialisePairNode(long documentID);