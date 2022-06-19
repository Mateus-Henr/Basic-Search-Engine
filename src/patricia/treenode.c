#include <stdio.h>
#include <string.h>

#include "treenode.h"


/*
 *  Initialises internal node with given values.
 *
 *  @param     left      pointer to tree node found on the left side of the one to be added.
 *  @param     right     pointer to tree node found on the right side of the one to be added.
 *  @param     index     index value to be stored in the tree node.
 *  @return              pointer to the initialised tree node.
 */
struct TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index)
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

    return newInternalNode;
}


/*
 *  Initialises internal node with given values.
 *
 *  @param     node     pointer to Node struct to be set as the value.
 *  @return             pointer to the initialised tree node.
 */
struct TreeNodeType *createExternalNode(struct Node *node)
{
    struct TreeNodeType *newExternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newExternalNode)
    {
        return NULL;
    }

    newExternalNode->nodeType = External;
    newExternalNode->TreeNode->node = node;

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
            printf("Element found.\n");
            return true;
        }

        printf("Element not found.\n");
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


int compareWords(int index, Node *node)
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
    return treeNodeType->nodeType == External;
}