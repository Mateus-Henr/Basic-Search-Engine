#include <stdbool.h>
#include "linkedlist/linkedlist.h"

typedef struct Hashtable
{
    LinkedList **linkedListsArray;
    int maxSize;
    int numberOfElements;
} Hashtable;

void initialiseHashtable(Hashtable *hashtable, int maxSize);

bool insert(Hashtable *hashtable, const char *word, long documentID);

void printHashtable(Hashtable *hashtable);

int getHashtableSize(Hashtable *hashtable);

bool isHashtableEmpty(Hashtable *hashtable);

void freeMemory(Hashtable *hashtable);

void sortAndPrintHashtable(Hashtable *hashtable);