/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

typedef struct PairNode
{
    long numberOfOccurrences;
    long documentID;
    struct PairNode *next;
} PairNode;

PairNode *initialisePairNode(long documentID);