#include <stdbool.h>
#include "pairlinkedlist/pairlinkedlist.h"

typedef enum
{
    Internal, External
} NodeType;

typedef struct ExternalNode
{
    char *word;
    PairLinkedList *pairSet;
} ExternalNode;

typedef struct
{
    int *index;
    char differChar;
    struct TreeNodeType *left;
    struct TreeNodeType *right;
} InternalNode;

typedef struct TreeNodeType
{
    NodeType nodeType;
    union
    {
        InternalNode *internalNode;
        ExternalNode *externalNode;
    } TreeNode;
} TreeNodeType;

TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int *index, char differChar);

TreeNodeType *createExternalNode(char *word, int documentID);

bool insertTreeNode(TreeNodeType **treeNodeType, char *word, long documentID);

int compareWords(const char *word, const int *index, char difChat);

bool isExternalNode(struct TreeNodeType *treeNodeType);

char findCharNode(const char *word, TreeNodeType *currNode, int *currIndex);

void printTreeNode(TreeNodeType *tree);
