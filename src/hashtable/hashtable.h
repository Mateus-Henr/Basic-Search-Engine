#include <stdbool.h>
#include "linkedlist/linkedlist.h"

typedef struct Hashtable
{
    LinkedList **linkedListArray;
    int *weights;
    int maxSize;
    long size;
} Hashtable;

void initialiseHashtable(Hashtable *hashtable, int sizeSuggestion);

bool insertIntoHashtable(Hashtable *hashtable, const char *word, long documentID);

long getHashtableSize(Hashtable *hashtable);

bool isHashtableEmpty(Hashtable *hashtable);

void printHashtable(Hashtable *hashtable);

void getTFIDFHashtable(Hashtable *hashtable, TFIDF *tfidf);

void sortAndPrintHashtable(Hashtable *hashtable);

void freeHashtable(Hashtable *hashtable);

void relevanceHashtable(Hashtable *hashtable, char **words, char **filenames, int numWords, int numDocs);