#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist/linkedlist.h"

#define D 8

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
        LinkedList *list;
    } *TreeNode;
} TreeNodeType;

int compareWords(int index, LinkedList *list);

bool isExternalNode(struct TreeNodeType *treeNodeType);

struct TreeNodeType *createInternalNode(struct TreeNodeType **left, struct TreeNodeType **right, int index);

struct TreeNodeType *createExternalNode(LinkedList *list);

void search(struct TreeNodeType *treeNodeType, LinkedList *list);

struct TreeNodeType *insertBetween(struct TreeNodeType **treeNodeType, int index, LinkedList *list);

struct TreeNodeType *insertIntoTree(struct TreeNodeType **treeNodeType, LinkedList *list);
