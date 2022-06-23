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
TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int *index, char differChar)
{
    struct TreeNodeType *newInternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newInternalNode)
    {
        return NULL;
    }
    newInternalNode->nodeType = Internal;
    newInternalNode->TreeNode.internalNode->left = *left;
    newInternalNode->TreeNode.internalNode->right = *right;
    newInternalNode->TreeNode.internalNode->differChar = differChar;
    newInternalNode->TreeNode.internalNode->index = index;

    return newInternalNode;
}


/*
 *  Initialises external externalNode with given values.
 *
 *  @param     externalNode     pointer to Node struct to be set as the value.
 *  @return                     pointer to the initialised tree external node.
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
        return NULL;
    }

    newExternalNode->TreeNode.externalNode->word = (char *) malloc(strlen(word));
    if (!word)
    {
        return NULL;
    }
    strcpy(newExternalNode->TreeNode.externalNode->word, word);

    newExternalNode->TreeNode.externalNode->pairSet = initialisePairLinkedList();
    if (!newExternalNode->TreeNode.externalNode->pairSet)
    {
        return NULL;
    }

    if (!pushPair(newExternalNode->TreeNode.externalNode->pairSet, documentID))
    {
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
        return strcmp(treeNodeType->TreeNode.externalNode->word, word) == 0 ? treeNodeType : NULL;
    }

    if (compareWords(word, treeNodeType->TreeNode.internalNode->index,
                     treeNodeType->TreeNode.internalNode->differChar) == 0)
    {
        return searchTreeNode(treeNodeType->TreeNode.internalNode->left, word);
    }
    else
    {
        return searchTreeNode(treeNodeType->TreeNode.internalNode->right, word);
    }
}


TreeNodeType *insertBetween(TreeNodeType **treeNodeType, char *word, int documentID, int *index, char differChar)
{
    if (isExternalNode(*treeNodeType) || index < (*treeNodeType)->TreeNode.internalNode->index)
    {
        TreeNodeType *treeNodeToAdd = createExternalNode(word, documentID);

        if (compareWords(word, (*treeNodeType)->TreeNode.internalNode->index,
                         (*treeNodeType)->TreeNode.internalNode->differChar) == 1)
        {
            return createInternalNode(treeNodeType, &treeNodeToAdd, index, differChar);
        }

        return createInternalNode(&treeNodeToAdd, treeNodeType, index, differChar);
    }

    if (compareWords(word, (*treeNodeType)->TreeNode.internalNode->index,
                     (*treeNodeType)->TreeNode.internalNode->differChar) == 1)
    {
        (*treeNodeType)->TreeNode.internalNode->right = insertBetween(
                &(*treeNodeType)->TreeNode.internalNode->right, word, documentID, index, differChar);
    }
    else
    {
        (*treeNodeType)->TreeNode.internalNode->right = insertBetween(
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
        if (compareWords(word, currTreeNodeType->TreeNode.internalNode->index,
                         currTreeNodeType->TreeNode.internalNode->differChar) == 1)
        {
            currTreeNodeType = currTreeNodeType->TreeNode.internalNode->left;
        }
        else
        {
            currTreeNodeType = currTreeNodeType->TreeNode.internalNode->right;
        }
    }

    int index = 0;
    char differChar = findCharNode(word, currTreeNodeType, &index);

    if (!strcmp(currTreeNodeType->TreeNode.externalNode->word, word))
    {
        PairNode *foundPairNode = searchPairNode((*treeNodeType)->TreeNode.externalNode->pairSet, documentID);

        if (foundPairNode)
        {
            foundPairNode->numberOfOccurrences++;
            return true;
        }

        return pushPair((*treeNodeType)->TreeNode.externalNode->pairSet, documentID);
    }

    return insertBetween(treeNodeType, word, documentID, &index, differChar);
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
        printf("%s\n", tree->TreeNode.externalNode->word);
    }

    if (!isExternalNode(tree))
    {
        printTreeNode(tree->TreeNode.internalNode->right);
    }
}


/*
 *  Finds the letter that differs in two words.
 */
char findCharNode(const char *word, TreeNodeType *currNode, int *currIndex)
{
    int currLetter = 0;

    while (currNode->TreeNode.externalNode->word[currLetter] && word[currLetter])
    {
        if (currNode->TreeNode.externalNode->word[currLetter] != word[currLetter])
        {
            *currIndex = currLetter;
            return currNode->TreeNode.externalNode->word[currLetter];
        }

        currLetter++;
    }

    *currIndex = (int) strlen(word) - 1;
    return word[*currIndex];
}


int compareWords(const char *word, const int *index, char difChar)
{
    return difChar > word[*index] ? 1 : 0;
}


/*
 *  Checks whether a given tree externalNode type is an external externalNode.
 *
 *  @param     treeNodeType    pointer to TreeNodeType struct.
 *  @return                    whether the externalNode is external or not.
 */
bool isExternalNode(struct TreeNodeType *treeNodeType)
{
    return (treeNodeType->nodeType == External);
}


//void freeTree(TreeNodeType * tree)
//{
//
//}
