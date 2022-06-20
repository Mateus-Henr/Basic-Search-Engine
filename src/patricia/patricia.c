#include <stdio.h>
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
 *  Checks if a word is in the tree.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 *  @param     word         word to look for.
 */
void search(PATRICIA *patricia, char *word)
{
    searchTreeNode(patricia->root, word);
    return;
}

bool insertIntoTree(PATRICIA *patricia, char *word)
{
    return insertTreeNode(patricia->root, word);
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