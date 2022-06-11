#include <stdbool.h>

#include "CrewMember.h"

typedef struct Hashtable
{
    CrewMember *crewMember[7];
    int size;
} Hashtable;

void initialiseHashtable(Hashtable *hashtable);

bool insert(Hashtable *hashtable, CrewMember *crewMember);

int getSize(Hashtable *hashtable);

bool isFull(Hashtable *hashtable);