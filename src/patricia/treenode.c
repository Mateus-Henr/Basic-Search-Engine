#include <stdio.h>
#include <string.h>

#include "treenode.h"


// Function prototype.
struct TreeNodeType *insertBetween(struct TreeNodeType **treeNodeType, int index, char *word);


/*
 *  Initialises internal node with given values.
 *
 *  @param     left      pointer to tree node found on the left side of the one to be added.
 *  @param     right     pointer to tree node found on the right side of the one to be added.
 *  @param     index     index value to be stored in the tree node.
 *  @return              pointer to the initialised tree node.
 */
struct TreeNodeType *
createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index, const char *word)
{
    struct TreeNodeType *newInternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newInternalNode)
    {
        return NULL;
    }
    newInternalNode->nodeType = Internal;
    newInternalNode->TreeNode->InternalNode->left = *left;
    newInternalNode->TreeNode->InternalNode->right = *right;
    newInternalNode->TreeNode->InternalNode->index = index;
    newInternalNode->TreeNode->InternalNode->differChar = word[0];

    return newInternalNode;
}


/*
 *  Initialises internal node with given values.
 *
 *  @param     node     pointer to Node struct to be set as the value.
 *  @return             pointer to the initialised tree node.
 */
struct TreeNodeType *createExternalNode(const char *word, int documentID)
{
    struct TreeNodeType *newExternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newExternalNode)
    {
        return NULL;
    }

    newExternalNode->nodeType = External;
    newExternalNode->TreeNode->node->word = word;
    newExternalNode->TreeNode->node->pairSet = initialisePairLinkedList();
    pushPair(newExternalNode->TreeNode->node->pairSet, documentID);

    if (!pushPair(newExternalNode->TreeNode->node->pairSet, documentID))
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
bool searchTreeNode(struct TreeNodeType *treeNodeType, const char *word)
{
    if (isExternalNode(treeNodeType))
    {
        if (!strcmp(treeNodeType->TreeNode->node->word, word))
        {
            return true;
        }

        return false;
    }

    if (compareWords(treeNodeType->TreeNode->InternalNode->index, word) == 0)
    {
        return searchTreeNode(treeNodeType->TreeNode->InternalNode->left, word);
    }
    else
    {
        return searchTreeNode(treeNodeType->TreeNode->InternalNode->right, word);
    }
}


struct TreeNodeType *insertBetween(struct TreeNodeType **treeNodeType, int index, Node *node, int documentID)
{
    if (isExternalNode(*treeNodeType) || index < (*treeNodeType)->TreeNode->InternalNode->index)
    {
        struct TreeNodeType *treeNode = createExternalNode(node, documentID);

        if (compareWords(index, node) == 1)
        {
            return createInternalNode(&treeNode, treeNodeType, index);
        }

        return createInternalNode(&treeNode, treeNodeType, index);
    }

    if (compareWords((*treeNodeType)->TreeNode->InternalNode->index, node) == 1)
    {
        (*treeNodeType)->TreeNode->InternalNode->right =
                insertBetween(&(*treeNodeType)->TreeNode->InternalNode->right, index, node);
    }
    else
    {
        (*treeNodeType)->TreeNode->InternalNode->left =
                insertBetween(&(*treeNodeType)->TreeNode->InternalNode->left, index, node);
    }

    return (*treeNodeType);
}


struct TreeNodeType *insertTreeNode(struct TreeNodeType **treeNodeType, const char *word, int documentID)
{
    if (!(*treeNodeType))
    {
        return createExternalNode(word, documentID);
    }

    struct TreeNodeType *currTreeNode = *treeNodeType;

    while (!isExternalNode(currTreeNode))
    {
        if (compareWords(currTreeNode->TreeNode->InternalNode->index, word) == 1)
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->right;
        }
        else
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->left;
        }
    }

    int currIndex = 1;

    while (compareWords((currIndex, word) == compareWords(currIndex, currTreeNode->TreeNode->node))
    {
        currIndex++;
    }

    if (currIndex > 8)
    {
        printf("ERROR: The specified key is already in the tree.\n");

        return *treeNodeType;
    }

    return insertBetween(treeNodeType, currIndex, node);
}


int compareWords(int index, const char *word)
{
    return 0;
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