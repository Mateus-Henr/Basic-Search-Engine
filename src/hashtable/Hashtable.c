#include <stddef.h>

#include "Hashtable.h"

int hash(int value);

void initialiseHashtable(Hashtable *hashtable)
{
    for (int i = 0; i < 7; i++)
    {
        hashtable->crewMember[i] = NULL;
    }

    hashtable->size = 0;
}

int getSize(Hashtable *hashtable)
{
    return hashtable->size;
}

bool isFull(Hashtable *hashtable)
{
    return getSize(hashtable) == 7;
}

bool insert(Hashtable *hashtable, CrewMember *crewMember)
{
    if (isFull(hashtable))
    {
        return false;
    }

    bool foundPosition = false;
    int hashedKey = hash(hashCode(crewMember));

    while (!foundPosition)
    {
        if (!hashtable->crewMember[hashedKey])
        {
            hashtable->crewMember[hashedKey] = crewMember;
            foundPosition = true;
        }

        hashedKey = hash(hashedKey + 1);
    }

    return true;
}

int hash(int value)
{
    return value % 7;
}