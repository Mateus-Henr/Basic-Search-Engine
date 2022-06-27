#include <stdbool.h>
#include "linkedlist/linkedlist.h"
/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

typedef struct Hashtable
{
    LinkedList **linkedListArray;
    int *weights;
    int maxSize;
    int numInsertions;
} Hashtable;

void initialiseHashtable(Hashtable *hashtable, int sizeSuggestion);

bool insertIntoHashtable(Hashtable *hashtable, const char *word, long documentID);

void sortAndPrintHashtable(Hashtable *hashtable);

void getTFIDFHashtable(Hashtable *hashtable, TFIDF *tfidf);

void relevanceHashtable(Hashtable *hashtable, char **words, char **filenames, int numWords, int numDocs);

long getSizeOfHashtable(Hashtable *hashtable);

void freeHashtable(Hashtable *hashtable);