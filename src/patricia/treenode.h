#include <stdlib.h>
#include <stdbool.h>
#include "pairlinkedlist/pairlinkedlist.h"

typedef enum
{
    Internal, External
} NodeType;

typedef struct
{
    const char *word;
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
            const char differChar;
            struct TreeNodeType *left;
            struct TreeNodeType *right;
        } *InternalNode;
        ExternalNode *node;
    } *TreeNode;
} TreeNodeType;

struct TreeNodeType *
createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index, const char *word);

struct TreeNodeType *createExternalNode(const char *word, int documentID);

bool searchTreeNode(struct TreeNodeType *treeNodeType, char *word);

struct TreeNodeType *insertTreeNode(struct TreeNodeType **treeNodeType, char *word);

int compareWords(int index, Node *node);

bool isExternalNode(struct TreeNodeType *treeNodeType);
