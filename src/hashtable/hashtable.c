#include <stddef.h>
#include "../linkedlist/linkedlist.h"

#include "hashtable.h"

int hash(int value);

void initialiseHashtable(Hashtable *hashtable)
{
    hashtable->size = 0;
}

bool isFull(Hashtable *hashtable)
{
    return hashtable->size;
}

bool insert(Hashtable *hashtable, char *word)
{
    if (isFull(hashtable))
    {
        return false;
    }

    return true;
}

int hash(int value)
{
    return value % 7;
}