#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "node.h"
/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

/*
 *  Initialises Node struct with given values.
 *
 *  @param     word          word to be inserted into the externalNode.
 *  @param     documentID    document's number (ID).
 *  @return                  pointer to the initialised externalNode.
 */
struct Node *initialiseNode(const char *word, long documentID)
{
    struct Node *nodeToAdd = (struct Node *) malloc(sizeof(struct Node));

    if (!nodeToAdd)
    {
        return NULL;
    }

    nodeToAdd->word = (char *) malloc(strlen(word) + 1);

    if (!nodeToAdd->word)
    {
        free(nodeToAdd);
        return NULL;
    }

    strcpy(nodeToAdd->word, word);
    nodeToAdd->pairSet = initialisePairLinkedList();

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

    nodeToAdd->next = NULL;

    return nodeToAdd;
}


/*
 *  Initialises a new pointer with existent externalNode content.
 *
 *  @param     externalNode     pointer to Node struct.
 *  @return                     pointer to the new pointer address.
 */
struct Node *initialiseNodeWithExistentData(struct Node *node)
{
    struct Node *copiedNode = (struct Node *) malloc(sizeof(struct Node));

    copiedNode->word = node->word;
    copiedNode->pairSet = node->pairSet;
    copiedNode->next = NULL;

    return copiedNode;
}


/*
 *  Compares one word against another character by character.
 *
 *  @param     word            first word to compare.
 *  @param     anotherWord     second word to compare.
 *  @return                    1 if the first word is greater, otherwise -1.
 */
int compareAlphabetically(const char *word, const char *anotherWord)
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

    return *word ? 1 : -1;
}


/*
 *  Gets the hashcode of a word based on a weights array.
 *
 *  @param     word        word to get its hashcode.
 *  @param     weights     array of weights.
 *  @return                hash code for the word.
 */
int hashCode(const char *word, const int *weights)
{
    int hashCode = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hashCode += word[i] * weights[i];
    }

    return hashCode;
}