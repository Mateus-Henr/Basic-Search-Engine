#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "hashtable.h"

int hash(Hashtable *hashtable, int value);

void initialiseHashtable(Hashtable *hashtable, int maxSize)
{
    hashtable->linkedListsArray = (LinkedList **) malloc(sizeof(LinkedList *) * maxSize);

    for (int i = 0; i < maxSize; i++)
    {
        hashtable->linkedListsArray[i] = NULL;
    }

    hashtable->maxSize = maxSize;
    hashtable->numberOfElements = 0;
}

bool insert(Hashtable *hashtable, const char *word, long documentID)
{
    int hashedKey = hash(hashtable, hashCode(word));

    if (!hashtable->linkedListsArray[hashedKey])
    {
        hashtable->linkedListsArray[hashedKey] = initialiseLinkedList();

        if (!hashtable->linkedListsArray[hashedKey])
        {
            return false;
        }
    }

    if (!push(hashtable->linkedListsArray[hashedKey], word, documentID))
    {
        return false;
    }

    hashtable->numberOfElements++;

    return true;
}

int hash(Hashtable *hashtable, int value)
{
    return abs(value % hashtable->maxSize);
}

bool isHashtableEmpty(Hashtable *hashtable)
{
    return hashtable->numberOfElements == 0;
}

void printHashtable(Hashtable *hashtable)
{
    if (isHashtableEmpty(hashtable))
    {
        printf("EMPTY.\n");
        return;
    }

    for (int i = 0; i < hashtable->maxSize; i++)
    {
        if (!hashtable->linkedListsArray[i])
        {
            printf("NULL\n");
        }
        else
        {
            printLinkedList(hashtable->linkedListsArray[i]);
        }
    }
}