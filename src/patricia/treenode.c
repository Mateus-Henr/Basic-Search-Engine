#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "treenode.h"


/*
 *  Initialises internal node with given values.
 *
 *  @param     left      pointer to tree node found on the left side of the one to be added.
 *  @param     right     pointer to tree node found on the right side of the one to be added.
 *  @param     index     index value to be stored in the tree node.
 *  @return              pointer to the initialised tree node.
 */
TreeType createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int *index, char differChar)
{
    struct TreeNodeType *newInternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newInternalNode)
    {
        return NULL;
    }
    newInternalNode->nodeType = Internal;
    newInternalNode->TreeNode->InternalNode->left = *left;
    newInternalNode->TreeNode->InternalNode->right = *right;
    newInternalNode->TreeNode->InternalNode->differChar = differChar;
    newInternalNode->TreeNode->InternalNode->index = index;

    return newInternalNode;
}


/*
 *  Initialises internal node with given values.
 *
 *  @param     node     pointer to Node struct to be set as the value.
 *  @return             pointer to the initialised tree node.
 */
TreeType createExternalNode(char *word, int numFiles)
{
    struct TreeNodeType *newExternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newExternalNode)
    {
        return NULL;
    }

    newExternalNode->nodeType = External;
    newExternalNode->TreeNode->node->word = word;
    newExternalNode->TreeNode->node->pairSet = initialisePairLinkedList();
    pushPair(newExternalNode->TreeNode->node->pairSet, numFiles);

    if (!pushPair(newExternalNode->TreeNode->node->pairSet, numFiles))
    {
        return NULL;
    }


    return newExternalNode;
}


/*
 *  Checks if a word is in the tree.
 *
 *  @param
 */
void searchTreeNode(struct TreeNodeType *treeNodeType, char *word)
{
    if (isExternalNode(treeNodeType))
    {
        if (treeNodeType->TreeNode->node->word == word)
        {
            printf("\nElement %s found!\n", word);
            return;
        }
        else
        {
            printf("\nElement %s not found!\n", word);
            return;
        }

    }

    if (compareWords(word, treeNodeType->TreeNode->InternalNode->index,
                     treeNodeType->TreeNode->InternalNode->differChar) == 0)
    {
        return searchTreeNode(treeNodeType->TreeNode->InternalNode->left, word);
    }
    else
    {
        return searchTreeNode(treeNodeType->TreeNode->InternalNode->right, word);
    }
}


TreeType insertBetween(TreeType *treeNodeType, char *word, int numFiles, int *index, char differChar)
{
    if (isExternalNode(*treeNodeType) || index < (*treeNodeType)->TreeNode->InternalNode->index)
    {
        TreeType treeNodeToAdd = createExternalNode(word, numFiles);

        if (compareWords(word, (*treeNodeType)->TreeNode->InternalNode->index,
                         (*treeNodeType)->TreeNode->InternalNode->differChar) == 1)
        {
            return createInternalNode(treeNodeType, &treeNodeToAdd, index, differChar);
        }
        else
        {
            return createInternalNode(&treeNodeToAdd, treeNodeType, index, differChar);
        }
    }

    if (compareWords(word, (*treeNodeType)->TreeNode->InternalNode->index,
                     (*treeNodeType)->TreeNode->InternalNode->differChar) == 1)
    {
        (*treeNodeType)->TreeNode->InternalNode->right = insertBetween(
                &(*treeNodeType)->TreeNode->InternalNode->right, word, numFiles, index, differChar);
    }
    else
    {
        (*treeNodeType)->TreeNode->InternalNode->right = insertBetween(
                &(*treeNodeType)->TreeNode->InternalNode->left, word, numFiles, index, differChar);
    }

    return *treeNodeType;
}


TreeType insertTreeNode(TreeType *treeNodeType, char *word, long documentID)
{
    if (!(*treeNodeType))
    {
        return createExternalNode(word, documentID);
    }

    TreeType currTreeNode = *treeNodeType;

    while (!isExternalNode(currTreeNode))
    {
        if (compareWords(word, currTreeNode->TreeNode->InternalNode->index,
                         currTreeNode->TreeNode->InternalNode->differChar) == 1)
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->left;
        }
        else
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->right;
        }
    }

    int index = 0;
    char differChar = findCharNode(word, currTreeNode, &index);

    if (currTreeNode->TreeNode->InternalNode->right->TreeNode->node->word == word ||
        currTreeNode->TreeNode->InternalNode->left->TreeNode->node->word == word)
    {
        if (!pushPair((*treeNodeType)->TreeNode->node->pairSet, documentID))
        {
            return NULL;
        }

        return (*treeNodeType);
    }

    return insertBetween(treeNodeType, word, documentID, &index, differChar);
}


void printTree(TreeNodeType *tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (!isExternalNode(tree))
    {
        printTree(tree->TreeNode->InternalNode->left);
    }
    else
    {
        printf("%s\n", tree->TreeNode->node->word);
    }

    if (!isExternalNode(tree))
    {
        printTree(tree->TreeNode->InternalNode->right);
    }
}


char findCharNode(const char *word, TreeNodeType *currNode, int *currIndex)
{
    int currLetter = 0;

    while (currNode->TreeNode->node->word[currLetter] && word[currLetter])
    {
        if (currNode->TreeNode->node->word[currLetter] != word[currLetter])
        {
            *currIndex = currLetter;
            return currNode->TreeNode->node->word[currLetter];
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
 *  Checks whether a given tree node type is an external node.
 *
 *  @param     treeNodeType    pointer to TreeNodeType struct.
 *  @return                    whether the node is external or not.
 */
bool isExternalNode(struct TreeNodeType *treeNodeType)
{
    return (treeNodeType->nodeType == External);
}


//void freeTree(TreeType tree)
//{
//
//}
