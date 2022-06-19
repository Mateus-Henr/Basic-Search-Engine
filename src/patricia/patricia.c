#include <stdio.h>

#include "patricia.h"


unsigned char Bit(unsigned char index, LinkedList *list)
{
    if (index == 0)
    {
        return 0;
    }

    int c = list;

    for (int j = 1; j <= D - index; j++)
    {
        c /= 2;
    }

    return (c & 1);
}


bool isExternal(struct TreeNodeType *treeNodeType)
{
    return treeNodeType->nodeType == External;
}


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


struct TreeNodeType *createExternalNode(LinkedList *list)
{
    struct TreeNodeType *newExternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newExternalNode)
    {
        return NULL;
    }

    newExternalNode->nodeType = External;
    newExternalNode->TreeNode->list = list;

    return newExternalNode;
}


void search(struct TreeNodeType *treeNodeType, LinkedList *list)
{
    if (isExternal(treeNodeType))
    {
        if (list == treeNodeType->TreeNode->list)
        {
            printf("Element found.\n");
        }
        else
        {
            printf("Element not found.\n");
        }

        return;
    }

    if (Bit(treeNodeType->TreeNode->InternalNode->index, list) == 0)
    {
        search(treeNodeType->TreeNode->InternalNode->left, list);
    }
    else
    {
        search(treeNodeType->TreeNode->InternalNode->right, list);
    }
}


struct TreeNodeType *insertBetween(struct TreeNodeType **treeNodeType, int index, LinkedList *list)
{
    if (isExternal(*treeNodeType) || index < (*treeNodeType)->TreeNode->InternalNode->index)
    {
        struct TreeNodeType *treeNode = createExternalNode(list);

        if (Bit(index, list) == 1)
        {
            return createInternalNode(&treeNode, treeNodeType, index);
        }

        return createInternalNode(&treeNode, treeNodeType, index);
    }

    if (Bit((*treeNodeType)->TreeNode->InternalNode->index, list) == 1)
    {
        (*treeNodeType)->TreeNode->InternalNode->right =
                insertBetween(&(*treeNodeType)->TreeNode->InternalNode->right, index, list);
    }
    else
    {
        (*treeNodeType)->TreeNode->InternalNode->left =
                insertBetween(&(*treeNodeType)->TreeNode->InternalNode->left, index, list);
    }

    return (*treeNodeType);
}


struct TreeNodeType *insertIntoTree(struct TreeNodeType **treeNodeType, LinkedList *list)
{
    if (!(*treeNodeType))
    {
        return createExternalNode(list);
    }

    struct TreeNodeType *currTreeNode = *treeNodeType;

    while (!isExternal(currTreeNode))
    {
        if (Bit(currTreeNode->TreeNode->InternalNode->index, list) == 1)
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->right;
        }
        else
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->left;
        }
    }

    int currIndex = 1;

    while ((currIndex <= D) & (Bit((int) currIndex, list) == Bit((int) currIndex, currTreeNode->TreeNode->list)))
    {
        currIndex++;
    }

    if (currIndex > D)
    {
        printf("ERROR: The specified key is already in the tree.\n");

        return *treeNodeType;
    }

    return insertBetween(treeNodeType, currIndex, list);
}