#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "node.h"


struct Node *initialiseNode(const char *word, long documentID)
{
    struct Node *nodeToAdd = (struct Node *) malloc(sizeof(struct Node));

    if (!nodeToAdd)
    {
        return NULL;
    }

    nodeToAdd->word = (char *) malloc(sizeof(strlen(word)) + 1);

    if (!nodeToAdd->word)
    {
        free(nodeToAdd);
        return NULL;
    }

    strcpy(nodeToAdd->word, word);
    nodeToAdd->pairSet = initialisePairLinkedList();
    nodeToAdd->next = NULL;

    if (!nodeToAdd->pairSet)
    {
        free(nodeToAdd);
        return NULL;
    }

    if (!pushPair(nodeToAdd->pairSet, documentID))
    {
        free(nodeToAdd->pairSet);
        free(nodeToAdd);
        return NULL;
    }

    return nodeToAdd;
}


int hashCode(const char *word)
{
    int hashCode = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hashCode += word[i] * (i + 1);
    }

    return hashCode;
}