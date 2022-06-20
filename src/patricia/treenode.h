#include <stdlib.h>
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

typedef struct TreeNodeType
{
    NodeType nodeType;
    union
    {
        struct
        {
            unsigned char index;
            char differChar;
            struct TreeNodeType *left;
            struct TreeNodeType *right;
        } *InternalNode;
        ExternalNode *node;
    } *TreeNode;
} TreeNodeType;

struct TreeNodeType *
createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index, char *word);

struct TreeNodeType *createExternalNode(char *word, int documentID);

void searchTreeNode(struct TreeNodeType *treeNodeType, char *word);

struct TreeNodeType *insertTreeNode(struct TreeNodeType **treeNodeType, char *word);

int compareWords(char *word, int index, char difChat);

bool isExternalNode(struct TreeNodeType *treeNodeType);
