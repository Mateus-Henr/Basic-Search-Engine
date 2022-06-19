#include <stdio.h>
#include "patricia.h"


// Function prototype.
struct TreeNodeType *insertBetween(struct TreeNodeType **treeNodeType, int index, Node *node);


/*
 *  Initialises PATRICIA struct with default values;
 */
void initialisePATRICIA(PATRICIA *patricia)
{
    patricia->root = (TreeNodeType *) malloc(sizeof(TreeNodeType));
    patricia->root = NULL;
    patricia->size = 0;
}


struct TreeNodeType *insertBetween(struct TreeNodeType **treeNodeType, int index, Node *node)
{
    if (isExternalNode(*treeNodeType) || index < (*treeNodeType)->TreeNode->InternalNode->index)
    {
        struct TreeNodeType *treeNode = createExternalNode(node);

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


struct TreeNodeType *insertIntoTree(struct TreeNodeType **treeNodeType, Node *node)
{
    if (!(*treeNodeType))
    {
        return createExternalNode(node);
    }

    struct TreeNodeType *currTreeNode = *treeNodeType;

    while (!isExternalNode(currTreeNode))
    {
        if (compareWords(currTreeNode->TreeNode->InternalNode->index, node) == 1)
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->right;
        }
        else
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->left;
        }
    }

    int currIndex = 1;

    while ((compareWords((int) currIndex, node) ==
            compareWords((int) currIndex, currTreeNode->TreeNode->node)))
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


/*
 *  Checks if a word is in the tree.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 *  @param     word         word to look for.
 */
bool search(PATRICIA *patricia, const char *word)
{
    return searchTreeNode(patricia->root, word);
}


/*
 *  Gets the tree's size.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 *  @return                 number of words in the tree.
 */
int getTreeSize(PATRICIA *patricia)
{
    return patricia->size;
}