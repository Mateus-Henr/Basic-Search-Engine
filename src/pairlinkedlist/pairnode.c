#include <stdlib.h>
#include <stddef.h>

#include "pairnode.h"


/*
 *  Initialises PairNode struct with default values.
 *
 *  @param     documentID    document's number (ID).
 *  @return                  pointer to the initialised externalNode.
 */
PairNode *initialisePairNode(long documentID)
{
    struct PairNode *pairNode = (struct PairNode *) malloc(sizeof(struct PairNode));

    if (!pairNode)
    {
        return NULL;
    }

    pairNode->documentID = documentID;
    pairNode->numberOfOccurrences = 1;
    pairNode->next = NULL;

    return pairNode;
}