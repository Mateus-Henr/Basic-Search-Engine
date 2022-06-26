#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "treenode.h"


// Function prototype.
TreeNodeType *searchTreeNode(struct TreeNodeType *treeNodeType, char *word);


/*
 *  Initialises internal externalNode with given values.
 *
 *  @param     left      pointer to tree externalNode found on the left side of the one to be added.
 *  @param     right     pointer to tree externalNode found on the right side of the one to be added.
 *  @param     index     index value to be stored in the tree externalNode.
 *  @return              pointer to the initialised tree externalNode.
 */
TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index, char differChar)
{
    struct TreeNodeType *newInternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newInternalNode)
    {
        return NULL;
    }
    newInternalNode->nodeType = Internal;

    newInternalNode->TreeNode.internalNode = (InternalNode *) malloc(sizeof(InternalNode));
    if (!newInternalNode->TreeNode.internalNode)
    {
        free(newInternalNode);
        return NULL;
    }

    newInternalNode->TreeNode.internalNode->left = *left;
    newInternalNode->TreeNode.internalNode->right = *right;
    newInternalNode->TreeNode.internalNode->differChar = differChar;
    newInternalNode->TreeNode.internalNode->index = index;

    return newInternalNode;
}


/*
 *  Initialises external externalNode with given values.
 *
 *  @param     word           word to be stored in the node.
 *  @param     documentID     id of the document.
 *  @return                   pointer to the initialised external node.
 */
TreeNodeType *createExternalNode(char *word, int documentID)
{
    struct TreeNodeType *newExternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newExternalNode)
    {
        return NULL;
    }

    newExternalNode->nodeType = External;

    newExternalNode->TreeNode.externalNode = (ExternalNode *) malloc(sizeof(ExternalNode));
    if (!newExternalNode->TreeNode.externalNode)
    {
        free(newExternalNode);
        return NULL;
    }

    newExternalNode->TreeNode.externalNode->word = (char *) malloc(strlen(word));
    if (!word)
    {
        free(newExternalNode->TreeNode.externalNode);
        free(newExternalNode);
        return NULL;
    }
    strcpy(newExternalNode->TreeNode.externalNode->word, word);

    newExternalNode->TreeNode.externalNode->pairSet = initialisePairLinkedList();
    if (!newExternalNode->TreeNode.externalNode->pairSet)
    {
        free(word);
        free(newExternalNode->TreeNode.externalNode);
        free(newExternalNode);
        return NULL;
    }

    if (!pushPair(newExternalNode->TreeNode.externalNode->pairSet, documentID))
    {
        free(newExternalNode->TreeNode.externalNode->pairSet);
        free(word);
        free(newExternalNode->TreeNode.externalNode);
        free(newExternalNode);
        return NULL;
    }

    return newExternalNode;
}


/*
 *  Searches for a tree externalNode in the tree.
 *
 *  @param     treeNodeType     pointer to TreeNodeType struct.
 *  @param     word             word to look for.
 *  @return                     found externalNode or null.
 */
TreeNodeType *searchTreeNode(struct TreeNodeType *treeNodeType, char *word)
{
    if (isExternalNode(treeNodeType))
    {
        return !strcmp(treeNodeType->TreeNode.externalNode->word, word) ? treeNodeType : NULL;
    }

    if (!isWordGreaterOrEqualThanChar(word, treeNodeType->TreeNode.internalNode->index,
                                      treeNodeType->TreeNode.internalNode->differChar))
    {
        return searchTreeNode(treeNodeType->TreeNode.internalNode->left, word);
    }
    else
    {
        return searchTreeNode(treeNodeType->TreeNode.internalNode->right, word);
    }
}


TreeNodeType *insertBetween(TreeNodeType **treeNodeType, char *word, int documentID, int index, char differChar)
{
    if (isExternalNode(*treeNodeType) || index < (*treeNodeType)->TreeNode.internalNode->index)
    {
        TreeNodeType *treeNodeToAdd = createExternalNode(word, documentID);

        if (isWordGreaterOrEqualThanChar(word, index, differChar))
        {
            return createInternalNode(treeNodeType, &treeNodeToAdd, index, differChar);
        }

        return createInternalNode(&treeNodeToAdd, treeNodeType, index, differChar);
    }

    if (isWordGreaterOrEqualThanChar(word, (*treeNodeType)->TreeNode.internalNode->index,
                                     (*treeNodeType)->TreeNode.internalNode->differChar))
    {
        (*treeNodeType)->TreeNode.internalNode->right = insertBetween(
                &(*treeNodeType)->TreeNode.internalNode->right, word, documentID, index, differChar);
    }
    else
    {
        (*treeNodeType)->TreeNode.internalNode->left = insertBetween(
                &(*treeNodeType)->TreeNode.internalNode->left, word, documentID, index, differChar);
    }

    return *treeNodeType;
}


bool insertTreeNode(TreeNodeType **treeNodeType, char *word, long documentID)
{
    if (!(*treeNodeType))
    {
        *treeNodeType = createExternalNode(word, documentID);
        return *treeNodeType;
    }

    TreeNodeType *currTreeNodeType = *treeNodeType;

    while (!isExternalNode(currTreeNodeType))
    {
        if (isWordGreaterOrEqualThanChar(word, currTreeNodeType->TreeNode.internalNode->index,
                                         currTreeNodeType->TreeNode.internalNode->differChar))
        {
            currTreeNodeType = currTreeNodeType->TreeNode.internalNode->right;
        }
        else
        {
            currTreeNodeType = currTreeNodeType->TreeNode.internalNode->left;
        }
    }

    int index = 0;
    char differChar = getDifferChar(word, currTreeNodeType, &index);

    if (!strcmp(currTreeNodeType->TreeNode.externalNode->word, word))
    {
        PairNode *foundPairNode = searchPairNode(currTreeNodeType->TreeNode.externalNode->pairSet, documentID);

        if (foundPairNode)
        {
            foundPairNode->numberOfOccurrences++;
            return true;
        }

        return pushPair(currTreeNodeType->TreeNode.externalNode->pairSet, documentID);
    }

    *treeNodeType = insertBetween(treeNodeType, word, documentID, index, differChar);

    return true;
}


/*
 *  Finds the letter that differs in two words.
 *
 *  @param     word     word to be searched in.
 *  @param
 */
char getDifferChar(const char *word, TreeNodeType *currNode, int *currIndex)
{
    int currLetter = 0;

    while (currNode->TreeNode.externalNode->word[currLetter] && word[currLetter])
    {
        if (currNode->TreeNode.externalNode->word[currLetter] != word[currLetter])
        {
            *currIndex = currLetter;

            if (currNode->TreeNode.externalNode->word[currLetter] > word[currLetter])
            {
                return currNode->TreeNode.externalNode->word[currLetter];
            }

            return word[currLetter];
        }

        currLetter++;
    }

    int wordLength = (int) strlen(word);
    int nodeWordLength = (int) strlen(currNode->TreeNode.externalNode->word);

    if (nodeWordLength == wordLength)
    {
        return word[wordLength - 1];
    }
    else if (nodeWordLength > wordLength)
    {
        *currIndex = wordLength;
        return currNode->TreeNode.externalNode->word[*currIndex];
    }

    *currIndex = nodeWordLength;
    return word[*currIndex];
}


/*
 *  Checks whether a word in a specified index is greater or equal than a character.
 *
 *  @param     word           word to be compared.
 *  @param     index          index in the word.
 *  @param     differChar     char to be compared against.
 *  @return                   whether the letter in the word is greater or equal than the char.
 */
bool isWordGreaterOrEqualThanChar(const char *word, int index, char differChar)
{
    int wordLength = (int) strlen(word);

    if (index >= wordLength)
    {
        return false;
    }

    return word[index] >= differChar;
}


/*
 *  Checks whether a given tree externalNode type is an external externalNode.
 *
 *  @param     treeNodeType    pointer to TreeNodeType struct.
 *  @return                    whether the externalNode is external or not.
 */
bool isExternalNode(struct TreeNodeType *treeNodeType)
{
    return treeNodeType->nodeType == External;
}


/*
 *  Prints out nodes by using jumping from one to the next.
 *
 *  @param     tree     pointer to TreeNodeType struct.
 */
void printTreeNode(TreeNodeType *tree)
{
    if (!tree)
    {
        printf("EMPTY.\n");
        return;
    }

    if (!isExternalNode(tree))
    {
        printTreeNode(tree->TreeNode.internalNode->left);
    }
    else
    {
        printf("%s ", tree->TreeNode.externalNode->word);
        printPairLinkedList(tree->TreeNode.externalNode->pairSet);
        printf("\n");
    }

    if (!isExternalNode(tree))
    {
        printTreeNode(tree->TreeNode.internalNode->right);
    }
}


/*
 *  Calculates TF-IDF and put result into TFIDF struct.
 *
 *  @param     treeNode     pointer to TreeNodeType struct.
 *  @param     tfidf        pointer to TFIDF struct.
 */
void getTFIDFTreeNodes(TreeNodeType *treeNode, TFIDF *tfidf)
{
    if (!isExternalNode(treeNode))
    {
        getTFIDFTreeNodes(treeNode->TreeNode.internalNode->left, tfidf);
    }
    else
    {
        getTFIDFPairLinkedList(treeNode->TreeNode.externalNode->pairSet, tfidf,
                               !strcmp(treeNode->TreeNode.externalNode->word, tfidf->word));
    }

    if (!isExternalNode(treeNode))
    {
        getTFIDFTreeNodes(treeNode->TreeNode.internalNode->right, tfidf);
    }
}


/*
 *  Deallocates tree node in the tree from memory.
 *
 *  @param     tree     head node of the tree.
 */
void freeTreeNodes(TreeNodeType *tree)
{
    if (tree)
    {
        if (!isExternalNode(tree))
        {
            freeTreeNodes(tree->TreeNode.internalNode->left);
        }
        else
        {
            if (tree->TreeNode.externalNode)
            {
                if (tree->TreeNode.externalNode->word)
                {
                    free(tree->TreeNode.externalNode->word);
                }

                if (tree->TreeNode.externalNode->pairSet)
                {
                    freePairLinkedList(tree->TreeNode.externalNode->pairSet);
                }

                free(tree->TreeNode.externalNode);
            }
        }

        if (!isExternalNode(tree))
        {
            freeTreeNodes(tree->TreeNode.internalNode->right);
        }

        free(tree);
    }
}