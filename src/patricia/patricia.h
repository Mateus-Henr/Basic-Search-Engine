
#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 26

struct Trie
{
    int isLeaf;             // 1 when the node is a leaf node
    struct Trie* character[CHAR_SIZE];
};


// Function

struct Trie* getNewTrieNode();
void insert(struct Trie *head, char* str);
int search(struct Trie* head, char* str);
int hasChildren(struct Trie* curr);
int deletion(struct Trie **curr, char* str);
