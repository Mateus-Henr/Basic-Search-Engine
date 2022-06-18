#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist/linkedlist.h"

#ifndef TADPATRICIA_H
#define TADPATRICIA_H

#ifdef __cplusplus
extern "C" {
#endif

#define TRUE 1
#define FALSE !TRUE
typedef  char *String;

typedef char *string;
typedef short boolean;

typedef enum
{
    Interno, Externo
} TipoNo;

typedef struct TipoPatNo *TArvore;
typedef struct TipoPatNo
{
    TipoNo nt;
    union
    {
        String Chave;
        struct
        {
            short Index;
            char Caractere;
            TArvore Esq, Dir;
        } NInterno;
    } NO;

    struct
    {
        LinkedList lista;
        int tamanho;
    } NoLista;

} TipoPatNo;

char Caractere(short i, String k);

boolean MenorIgual(char a, char b);

boolean EExterno(TArvore p);

TArvore CriaNoInt(short i, TArvore *Esq, TArvore *Dir, char Caractere);

TArvore CriaNoExt(String k, int idDoc);

boolean pesquisaOcorrencia(String k, TArvore t, int idDoc);

float retornaPesoTermo(String k, TArvore t, int idDoc);

void imprimirNo(TArvore no);

void imprimirOrdem(TArvore ap);

TArvore InsereEntre(String k, TArvore *t, short i, int idDoc);

TArvore Insere(String k, TArvore *t, int idDoc);

string *nomeArquivos;
int *nPalavrasDistintas;
int nDoc;

#ifdef __cplusplus
}
#endif

#endif /* TADPATRICIA_H */


/*
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
*/