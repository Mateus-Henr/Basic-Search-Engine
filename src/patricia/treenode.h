#include <stdbool.h>
#include "pairlinkedlist/pairlinkedlist.h"

typedef enum
{
    Internal, External
} NodeType;
typedef struct  TreeNodeType* TreeType;
typedef struct ExternalNode
{
    char *word;
    PairLinkedList *pairSet;
} ExternalNode;

typedef struct TreeNodeType
{
    NodeType nodeType;
    union
    {
        struct
        {
            int *index;
            char differChar;
            struct TreeNodeType *left;
            struct TreeNodeType *right;
        } *InternalNode;
        ExternalNode *node;
    } *TreeNode;
} TreeNodeType;

TreeType createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int *index, char differChar);

TreeType createExternalNode(char *word, int documentID);

void searchTreeNode(struct TreeNodeType *treeNodeType, char *word);

TreeType insertTreeNode(TreeNodeType **treeNodeType, char *word, long documentID);

int compareWords(char *word, int *index, char difChat);

bool isExternalNode(struct TreeNodeType *treeNodeType);

char findCharNode(char *word, TreeNodeType *currNode,int *currIndex);
