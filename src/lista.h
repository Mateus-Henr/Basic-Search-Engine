#include <stdbool.h>

#include "processo.h"

/*
 * Estrutura abstrata para uma lista de processos ao qual simula processo de uma máquina.
 * A estrutura lista é composta pela estrutura célula onde que abriga um processo (tipo de dado que simula um processo),
 * além de possuir dois "Cursor" que são inteiros usados para interligar Células em que são dispostas em um array na
 * lista.
 * Além da estrutura lista possuir um array de "Celula", a mesma também possui um tamanho (tamanho da lista que será
 * usada pelo usuário), dois "Cursor" que são inteiros usados para apontar para a primeira e última célula na lista,
 * um inteiro que demostra a célula que está atualmente disponível para receber um processo e um inteiro que representa
 * o número de células sendo ocupadas no array.
 */

typedef int Cursor;

typedef struct
{
    TProcesso *processo;
    Cursor ant;
    Cursor prox;
} Celula;

typedef struct
{
    unsigned int tamanho;
    Celula *celulas;
    Cursor primeiro;
    Cursor ultimo;
    Cursor celulasDisp;
    int numCelOcupados;
} Lista;


// Função de inicialização

void inicializaLista(Lista *lista, unsigned int tamanho);

void destroiLista(Lista *lista);


// Operações

bool insereOrdenado(Lista *lista);

bool removeFrente(Lista *lista);

void imprimeData(Lista *lista);


// Getter

int tamanho(Lista *lista);

void check(Lista *lista);