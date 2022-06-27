/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */
#include <stdbool.h>
#include "treenode.h"

typedef struct
{
    TreeNodeType *root;
} PATRICIA;

void initialisePATRICIA(PATRICIA *patricia);

bool insertIntoTree(PATRICIA *patricia, char *word, int documentID);

void printTree(PATRICIA *patricia);

void getTFIDFPATRICIA(PATRICIA *patricia, TFIDF *tfidf);

void relevancePATRICIA(PATRICIA *tree, char **words, char **filenames, int numWords, int numDocs);

long getSizeOfPATRICIA(PATRICIA *patricia);

void freeTree(PATRICIA *patricia);