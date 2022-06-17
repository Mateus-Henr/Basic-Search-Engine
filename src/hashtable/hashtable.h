#include <stdbool.h>
#include "linkedlist/linkedlist.h"

typedef struct Hashtable
{
    LinkedList **linkedListsArray;
    int *weights;
    int maxSize;
    int numberOfElements;
} Hashtable;

void initialiseHashtable(Hashtable *hashtable, int sizeSuggestion);

bool insert(Hashtable *hashtable, const char *word, long documentID);

int getHashtableSize(Hashtable *hashtable);

bool isHashtableEmpty(Hashtable *hashtable);

void printHashtable(Hashtable *hashtable);

void getTermFrequencyInHashtable(Hashtable *hashtable, TFIDF *tfidf);

void sortAndPrintHashtable(Hashtable *hashtable);

void freeHashtable(Hashtable *hashtable);

void calculateRelevance(Hashtable *hashtable, char **words, int numWords, int numDocs);