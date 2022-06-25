#include <stdio.h>
#include <stdlib.h>

#include "patricia.h"


/*
 *  Initialises PATRICIA struct with default values;
 */
void initialisePATRICIA(PATRICIA *patricia)
{
    patricia->root = (TreeNodeType *) malloc(sizeof(TreeNodeType));
    patricia->root = NULL;
    patricia->size = 0;
}


/*
 *  Inserts externalNode into the tree.
 *
 *  @param     patricia       pointer to PATRICIA struct.
 *  @param     word           word to insertIntoHashtable.
 *  @param     documentID     document's ID.
 */
bool insertIntoTree(PATRICIA *patricia, char *word, int documentID)
{
    return insertTreeNode(&patricia->root, word, documentID);
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


/*
 *  Prints the PATRICIA tree out.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void printTree(PATRICIA *patricia)
{
    printTreeNode(patricia->root);
}


/*
 *  Deallocates structs that have been allocated dynamically.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void freeTree(PATRICIA *patricia)
{
    freeTreeNodes(patricia->root);
}