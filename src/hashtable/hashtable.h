#include <stdbool.h>

typedef struct Hashtable
{
    LinkedList *linkedList;
    int size;
} Hashtable;

void initialiseHashtable(Hashtable *hashtable);

bool insert(Hashtable *hashtable, char *word);

bool isFull(Hashtable *hashtable);