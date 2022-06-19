#include <stdio.h>

#include "patricia.h"


int compareWords(int index, LinkedList *list)
{
    return 0;
}


bool isExternalNode(struct TreeNodeType *treeNodeType)
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
    if (isExternalNode(treeNodeType))
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

    if (compareWords(treeNodeType->TreeNode->InternalNode->index, list) == 0)
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
    if (isExternalNode(*treeNodeType) || index < (*treeNodeType)->TreeNode->InternalNode->index)
    {
        struct TreeNodeType *treeNode = createExternalNode(list);

        if (compareWords(index, list) == 1)
        {
            return createInternalNode(&treeNode, treeNodeType, index);
        }

        return createInternalNode(&treeNode, treeNodeType, index);
    }

    if (compareWords((*treeNodeType)->TreeNode->InternalNode->index, list) == 1)
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

    while (!isExternalNode(currTreeNode))
    {
        if (compareWords(currTreeNode->TreeNode->InternalNode->index, list) == 1)
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->right;
        }
        else
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->left;
        }
    }

    int currIndex = 1;

    while ((compareWords((int) currIndex, list) ==
            compareWords((int) currIndex, currTreeNode->TreeNode->list)))
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