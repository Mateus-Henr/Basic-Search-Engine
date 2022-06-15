#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "hashtable.h"


// Function prototype
int hash(Hashtable *hashtable, int value);

int compareInAscendingOrder(const char *word, const char *anotherWord);


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

bool insertSorted(LinkedList *list, Node *node)
{
    struct Node *nodeCopy = initialisePointerFromExistent(node);

    if (isLinkedListEmpty(list))
    {
        list->head = nodeCopy;
        list->tail = nodeCopy;

        return true;
    }

    if (compareInAscendingOrder(list->tail->word, nodeCopy->word) == -1)
    {
        list->tail->next = nodeCopy;
        list->tail = nodeCopy;
    }
    else if (compareInAscendingOrder(list->head->word, nodeCopy->word) == 1)
    {
        nodeCopy->next = list->head;
        list->head = nodeCopy;
    }
    else
    {
        struct Node *currNode = list->head;

        while (currNode->next && compareInAscendingOrder(currNode->next->word, nodeCopy->word) != 1)
        {
            currNode = currNode->next;
        }

        nodeCopy->next = currNode->next;
        currNode->next = nodeCopy;
    }

    return true;
}

int compareInAscendingOrder(const char *word, const char *anotherWord)
{
    while (*word && *anotherWord)
    {
        if (*word > *anotherWord)
        {
            return 1;
        }
        else if (*word < *anotherWord)
        {
            return -1;
        }

        word++;
        anotherWord++;
    }

    if (*word)
    {
        return 1;
    }
    else
    {
        return -1;
    }
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
            printf("[%d] NULL\n", i);
        }
        else
        {
            printf("[%d] ", i);
            printLinkedList(hashtable->linkedListsArray[i]);
        }
    }
}


void freeMemory(Hashtable *hashtable)
{
    if (hashtable->linkedListsArray)
    {
        for (int i = 0; i < hashtable->maxSize; i++)
        {
            if (hashtable->linkedListsArray[i])
            {
                struct Node *currNode = hashtable->linkedListsArray[i]->head;

                while (currNode)
                {
                    if (currNode->word)
                    {
                        free(currNode->word);
                    }

                    if (currNode->pairSet)
                    {
                        struct PairNode *currPairNode = currNode->pairSet->head;

                        while (currPairNode)
                        {
                            struct PairNode *pairNodeToDelete = currPairNode;
                            currPairNode = currPairNode->next;
                            free(pairNodeToDelete);
                        }
                    }

                    struct Node *nodeToDelete = currNode;
                    currNode = currNode->next;
                    free(nodeToDelete);
                }
            }
        }

        free(hashtable->linkedListsArray);
    }
}


int getHashtableSize(Hashtable *hashtable)
{
    return hashtable->numberOfElements;
}


void convertToLinkedList(Hashtable *hashtable)
{
    LinkedList *list = initialiseLinkedList();

    for (int i = 0; i < hashtable->maxSize; i++)
    {
        if (hashtable->linkedListsArray[i])
        {
            struct Node *currNode = hashtable->linkedListsArray[i]->head;

            while (currNode)
            {
                insertSorted(list, currNode);
                currNode = currNode->next;
            }
        }
    }

    printLinkedList(list);
}