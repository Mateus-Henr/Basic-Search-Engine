#include<stdlib.h>
#include <stdbool.h>
#include <sys/time.h>

#define D 8   /* depende de KeyType */

typedef unsigned char KeyType
{
        char string[CHAR_MAX];
        ////tem q coloca aquela estrutura iDoc bosta
} KeyType;
typedef unsigned char TipoIndexAmp;
typedef unsigned char TipoDib;

typedef enum
{
    Internal, External
} NodeType;

typedef struct TreeNode
{
    NodeType nodeType;
    union
    {
        struct
        {
            TipoIndexAmp Index;
            char differChar;
            struct TreeNode *left;
            struct TreeNode *right;
        } InternalNode;
        KeyType string;
    } Node;
} TreeNode;

TipoDib Bit(TipoIndexAmp index, KeyType k);

bool isExternal(struct TreeNode *treeNode);

struct TreeNode *createIntNode(struct TreeNode **left, struct TreeNode **right, int index);

struct TreeNode *createExternalNode(KeyType k);

void search(struct TreeNode *treeNode, KeyType string);

struct TreeNode *insertBetween(struct TreeNode **t, int i, KeyType k);

struct TreeNode *insertIntoTree(struct TreeNode **treeNode, KeyType k);
