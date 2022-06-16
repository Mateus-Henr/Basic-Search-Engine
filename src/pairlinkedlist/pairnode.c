#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "pairnode.h"


/*
 *  Initialises PairNode struct with default values.
 *
 *  @param     documentID    document's number (ID).
 *  @return                  pointer to the initialised node.
 */
PairNode *initialisePairNode(long documentID)
{
    struct PairNode *node = (PairNode *) malloc(sizeof(PairNode));

    if (!node)
    {
        return NULL;
    }

    node->documentID = documentID;
    node->numberOfOccurrences = 1;
    node->next = NULL;

    return node;
}