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
    strcpy(nodeToAdd->word, word);
    nodeToAdd->pairSet = initialisePairLinkedList();
    nodeToAdd->next = NULL;

    if (!nodeToAdd->pairSet)
    {
        free(nodeToAdd);
        return NULL;
    }

    pushPair(nodeToAdd->pairSet, documentID);

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