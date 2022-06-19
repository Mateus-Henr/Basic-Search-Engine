#include <stdio.h>

#include "patricia.h"


TipoDib Bit(TipoIndexAmp index, KeyType k)
{
    if (index == 0)
    {
        return 0;
    }

    int c = k;

    for (int j = 1; j <= D - index; j++)
    {
        c /= 2;
    }

    return (c & 1);
}


bool isExternal(struct TreeNode *treeNode)
{
    return treeNode->nodeType == External;
}


struct TreeNode *createIntNode(struct TreeNode **left, struct TreeNode **right, int index)
{
    struct TreeNode *treeNode = (struct TreeNode *) malloc(sizeof(struct TreeNode));

    if (!treeNode)
    {
        return NULL;
    }

    treeNode->nodeType = Internal;
    treeNode->Node.InternalNode.left = *left;
    treeNode->Node.InternalNode.right = *right;
    treeNode->Node.InternalNode.Index = index;

    return treeNode;
}


struct TreeNode *createExternalNode(KeyType k)
{
    struct TreeNode *treeNode = (struct TreeNode *) malloc(sizeof(TreeNode));

    if (!treeNode)
    {
        return NULL;
    }

    treeNode->nodeType = External;
    treeNode->Node.string = k;

    return treeNode;
}


void search(struct TreeNode *treeNode, KeyType string)
{
    if (isExternal(treeNode))
    {
        if (string == treeNode->Node.string)
        {
            printf("Elemento encontrado\n");
        }
        else
        {
            printf("Elemento nao encontrado\n");
        }

        return;
    }

    if (Bit(treeNode->Node.InternalNode.Index, string) == 0)
    {
        search(treeNode->Node.InternalNode.left, string);
    }
    else
    {
        search(treeNode->Node.InternalNode.right, string);
    }
}


struct TreeNode *insertBetween(struct TreeNode **t, int i, KeyType k)
{
    if (isExternal(*t) || i < (*t)->Node.InternalNode.Index)
    {
        struct TreeNode *treeNode = createExternalNode(k);

        if (Bit(i, k) == 1)
        {
            return createIntNode(&treeNode, t, i);
        }

        return createIntNode(&treeNode, t, i);
    }

    if (Bit((*t)->Node.InternalNode.Index, k) == 1)
    {
        (*t)->Node.InternalNode.right = insertBetween(&(*t)->Node.InternalNode.right, i, k);
    }
    else
    {
        (*t)->Node.InternalNode.left = insertBetween(&(*t)->Node.InternalNode.left, i, k);
    }

    return (*t);
}


struct TreeNode *insertIntoTree(struct TreeNode **treeNode, KeyType k)
{
    if (!(*treeNode))
    {
        return createExternalNode(k);
    }

    struct TreeNode *currTreeNode = *treeNode;

    while (!isExternal(currTreeNode))
    {
        if (Bit(currTreeNode->Node.InternalNode.Index, k) == 1)
        {
            currTreeNode = currTreeNode->Node.InternalNode.right;
        }
        else
        {
            currTreeNode = currTreeNode->Node.InternalNode.left;
        }
    }

    int currIndex = 1;

    while ((currIndex <= D) & (Bit((int) currIndex, k) == Bit((int) currIndex, currTreeNode->Node.string)))
    {
        currIndex++;
    }

    if (currIndex > D)
    {
        printf("Erro: chave ja esta na arvore\n");

        return (*treeNode);
    }

    return (insertBetween(treeNode, currIndex, k));
}