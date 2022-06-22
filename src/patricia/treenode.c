#include <stdio.h>
#include <stdlib.h>
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
TreeType createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int *index, char differChar) {
    struct TreeNodeType *newInternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newInternalNode) {
        return NULL;
    }
    newInternalNode->nodeType = Internal;
    newInternalNode->TreeNode->InternalNode->left = *left;
    newInternalNode->TreeNode->InternalNode->right = *right;
    newInternalNode->TreeNode->InternalNode->differChar=differChar;
    newInternalNode->TreeNode->InternalNode->index = index;

    return newInternalNode;
}


/*
 *  Initialises internal node with given values.
 *
 *  @param     node     pointer to Node struct to be set as the value.
 *  @return             pointer to the initialised tree node.
 */
TreeType createExternalNode(char *word, int numFiles) {
    struct TreeNodeType *newExternalNode = (struct TreeNodeType *) malloc(sizeof(struct TreeNodeType));

    if (!newExternalNode) {
        return NULL;
    }

    newExternalNode->nodeType = External;
    newExternalNode->TreeNode->node->word = word;
    newExternalNode->TreeNode->node->pairSet = initialisePairLinkedList();
    pushPair(newExternalNode->TreeNode->node->pairSet, numFiles);

    if (!pushPair(newExternalNode->TreeNode->node->pairSet, numFiles)) {
        return NULL;
    }


    return newExternalNode;
}


/*
 *  Checks if a word is in the tree.
 *
 *  @param
 */
void searchTreeNode(struct TreeNodeType *treeNodeType, char *word) {
    if (isExternalNode(treeNodeType)) {
        if (treeNodeType->TreeNode->node->word== word) {
            printf("\nElement %s found!\n", word);
            return;
        } else {
            printf("\nElement %s not found!\n", word);
            return;
        }

    }

    if (compareWords(word, treeNodeType->TreeNode->InternalNode->index,
                     treeNodeType->TreeNode->InternalNode->differChar) == 0) {
        return searchTreeNode(treeNodeType->TreeNode->InternalNode->left, word);
    } else {
        return searchTreeNode(treeNodeType->TreeNode->InternalNode->right, word);
    }
}

TreeType insertBetween(TreeType *treeNodeType, char *word, int numFiles, int *index,char differChar){
    TreeType p;
    if(isExternalNode(*treeNodeType) || index<(*treeNodeType)->TreeNode->InternalNode->index){
        p= createExternalNode(word,numFiles);
        if(compareWords(word,(*treeNodeType)->TreeNode->InternalNode->index,(*treeNodeType)->TreeNode->InternalNode->differChar)==1){
            return createInternalNode(treeNodeType,&p,index,differChar);
        } else {
            return createInternalNode(&p,treeNodeType,index,differChar);
        }
    } else {
        if(compareWords(word,(*treeNodeType)->TreeNode->InternalNode->index,(*treeNodeType)->TreeNode->InternalNode->differChar)==1){
            (*treeNodeType)->TreeNode->InternalNode->right= insertBetween(&(*treeNodeType)->TreeNode->InternalNode->right,word,numFiles,index,differChar);
        } else {
            (*treeNodeType)->TreeNode->InternalNode->right= insertBetween(&(*treeNodeType)->TreeNode->InternalNode->left,word,numFiles,index,differChar);
        }
        return *treeNodeType;
    }
}

TreeType insertTreeNode(TreeType *treeNodeType, char *word, long documentID) {

    if (!(*treeNodeType))
    {
        return createExternalNode(word,  documentID);
    }

    TreeType currTreeNode = *treeNodeType;

    while (!isExternalNode(currTreeNode))
    {
        if (compareWords(word, currTreeNode->TreeNode->InternalNode->index,currTreeNode->TreeNode->InternalNode->differChar) == 1)
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->left;
        }
        else
        {
            currTreeNode = currTreeNode->TreeNode->InternalNode->right;
        }
    }
    int *index;
    char differChar = findCharNode(word,currTreeNode,index);
    if(currTreeNode->TreeNode->InternalNode->right->TreeNode->node->word==word || currTreeNode->TreeNode->InternalNode->left->TreeNode->node->word==word)
    {
        printf("The node %s already exist.", word);
        return (*treeNodeType);
    }
    else
    {
        return insertBetween(treeNodeType,word, documentID,index,differChar);
    }
}

void printTree(TreeNodeType *tree) {
    if (tree == NULL)
        return;
    if (!isExternalNode(tree))
        printTree(tree->TreeNode->InternalNode->left);
    else
        printf("%s\n", tree->TreeNode->node->word);
    if (!isExternalNode(tree))
        printTree(tree->TreeNode->InternalNode->right);
}

char findCharNode(char *word, TreeNodeType *currNode, int *currIndex) {
    int aux ;
    aux = 0;
    char differChar;

    while (true) {
        differChar = currNode->TreeNode->node->word[aux];
        if (currNode->TreeNode->node->word[aux] != word[aux])
            break;
        aux++;
    }
    currIndex = &aux;
    return differChar;
}

int compareWords(char *word, int *index, char difChar) {
    char letter ;
    letter = word[*index];

    if (difChar > letter) {
        return 1;
    } else {
        return 0;
    }

}

/*
 *  Checks whether a given tree node type is an external node.
 *
 *  @param     treeNodeType    pointer to TreeNodeType struct.
 *  @return                    whether the node is external or not.
 */
bool isExternalNode(struct TreeNodeType *treeNodeType) {
    return (treeNodeType->nodeType == External);
}

void freeTree(TreeType tree){

}
