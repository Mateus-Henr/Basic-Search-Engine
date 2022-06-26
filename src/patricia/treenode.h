#include <stdbool.h>
#include "pairlinkedlist/pairlinkedlist.h"

typedef enum
{
    Right, Left
} Direction;

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
    char differChar;
    int index;
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

TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index, char differChar);

TreeNodeType *createExternalNode(char *word, int documentID);

bool insertTreeNode(TreeNodeType **treeNodeType, char *word, long documentID);

bool isWordGreaterOrEqualThanChar(const char *word, int index, char differChar);

bool isExternalNode(struct TreeNodeType *treeNodeType);

char getDifferChar(const char *word, TreeNodeType *currNode, int *currIndex);

void printTreeNode(TreeNodeType *tree);

void getTFIDFTreeNodes(TreeNodeType *treeNode, TFIDF *tfidf);

void freeTreeNodes(TreeNodeType *tree);