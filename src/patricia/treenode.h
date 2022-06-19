#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist//node.h"


typedef enum
{
    Internal, External
} NodeType;

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
        struct Node *node;
    } *TreeNode;
} TreeNodeType;

struct TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index);

struct TreeNodeType *createExternalNode(struct Node *node);

bool searchTreeNode(struct TreeNodeType *treeNodeType, const char *word);

int compareWords(int index, Node *node);

bool isExternalNode(struct TreeNodeType *treeNodeType);
