#include <stdlib.h>
#include <stddef.h>

#include "pairnode.h"
/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

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