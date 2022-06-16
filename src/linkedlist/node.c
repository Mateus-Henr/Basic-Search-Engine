#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "node.h"


/*
 *  Initialises Node struct with given values.
 *
 *  @param     word          word to be inserted into the node.
 *  @param     documentID    document's number (ID).
 *  @return                  pointer to the initialised node.
 */
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


/*
 *  Initialises a new pointer with existent node content.
 *
 *  @param     node     pointer to Node struct.
 *  @return             pointer to the new pointer address.
 */
struct Node *initialisesNodeWithExistentOne(struct Node *node)
{
    struct Node *copiedNode = (struct Node *) malloc(sizeof(struct Node));

    copiedNode->word = node->word;
    copiedNode->pairSet = node->pairSet;
    copiedNode->next = NULL;

    return copiedNode;
}


/*
 *  Gets the hashcode of a word based on a weights array.
 *
 *  @param     word     word to get its hashcode.
 *  @return             hash code for the word.
 */
int hashCode(const char *word)
{
    int hashCode = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hashCode += word[i] * (i + 1);
    }

    return hashCode;
}