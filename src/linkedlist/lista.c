#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "lista.h"

#define FINAL_DA_LISTA -1
#define INICIO_DA_LISTA -1
#define INVALIDO -1
#define MENOS_UM -1;
#define VALOR_INICIAL 0
#define NENHUM_ELEMENTO 0
#define UM 1
#define LISTA_VAZIA "Lista Vazia!\n"
#define PRINT_ELEMENTO "\n\nPosicao elemento = %d\nPID = %d\nant = %d | prox = %d\n"


/*
 * Inicializa a estrutura Lista e seus componentes.
 *
 * @param    lista      ponteiro para a estrutura Lista.
 * @param    tamanho    tamanho do array que armazena os elementos da lista.
 */
void inicializaLista(Lista *lista, unsigned int tamanho)
{
    // Alocando espaço na memória para o array que compõe a estrutura lista (tamanho informado pelo usuário).
    lista->celulas = (Celula *) malloc(tamanho * sizeof(Celula));

    // Inicialização das células.
    for (int posicao = VALOR_INICIAL; posicao < tamanho; posicao++)
    {
        Celula celula;

        celula.processo = NULL;
        celula.ant = MENOS_UM;

        if (posicao == (tamanho - UM))
        {
            celula.prox = FINAL_DA_LISTA;
        }
        else
        {
            celula.prox = posicao + UM;
        }

        // Colocando célula no array.
        ((Celula *) lista->celulas)[posicao] = celula;
    }

    // Inicializando demais variáveis da lista.
    lista->tamanho = tamanho;
    lista->numCelOcupados = NENHUM_ELEMENTO;
    lista->celulasDisp = NENHUM_ELEMENTO;
}


/*
 * Retorna número atual de células sendo ocupadas na lista.
 *
 * @param    lista    ponteiro para a estrutura Lista.
 * @return            número de células ocupadas.
 */
int tamanho(Lista *lista)
{
    return lista->numCelOcupados;
}


/*
 * Cria um processo aleatório, e insere o mesmo ordenadamente na lista.
 *
 * @param    lista    ponteiro para a estrutura Lista.
 */
bool insereOrdenado(Lista *lista)
{
    // Checando se há célula disponível.
    if (lista->celulasDisp == INVALIDO)
    {
        return false;
    }

    Celula *celulas = (Celula *) lista->celulas;
    int proxCelulaDisp = celulas[lista->celulasDisp].prox;

    // Inicia um processo e adiciona-o no array.
    celulas[lista->celulasDisp].processo = inicializa_processo();

    // Primeiro elemento a ser adicionado na lista.
    if (tamanho(lista) == NENHUM_ELEMENTO)
    {
        celulas[lista->celulasDisp].prox = MENOS_UM;
        lista->primeiro = lista->celulasDisp;
        lista->ultimo = lista->celulasDisp;
    }
    else if (get_PID(celulas[lista->celulasDisp].processo) <= get_PID(celulas[lista->primeiro].processo))
    {
        celulas[lista->celulasDisp].prox = lista->primeiro;
        celulas[lista->primeiro].ant = lista->celulasDisp;
        lista->primeiro = lista->celulasDisp;
    }
    else if (get_PID(celulas[lista->celulasDisp].processo) >= get_PID(celulas[lista->ultimo].processo))
    {
        celulas[lista->ultimo].prox = lista->celulasDisp;
        celulas[lista->celulasDisp].ant = lista->ultimo;
        celulas[lista->celulasDisp].prox = MENOS_UM;
        lista->ultimo = lista->celulasDisp;
    }
    else
    {
        int elementoAtual = lista->primeiro;

        while (get_PID(celulas[lista->celulasDisp].processo) >= get_PID(celulas[elementoAtual].processo))
        {
            elementoAtual = celulas[elementoAtual].prox;
        }

        int antElementoAtual = celulas[elementoAtual].ant;

        celulas[antElementoAtual].prox = lista->celulasDisp;
        celulas[elementoAtual].ant = lista->celulasDisp;

        celulas[lista->celulasDisp].ant = antElementoAtual;
        celulas[lista->celulasDisp].prox = elementoAtual;
    }

    lista->celulasDisp = proxCelulaDisp;
    lista->numCelOcupados++;

    return true;
}


/*
 * Remove o elemento na primeira posição da lista.
 *
 * @param    lista    ponteiro para a estrutura Lista.
 * @return            sucesso na operação.
 */
bool removeFrente(Lista *lista)
{
    // Checando se a lista está vazia.
    if (tamanho(lista) == NENHUM_ELEMENTO)
    {
        return false;
    }

    Celula *celulas = (Celula *) lista->celulas;

    // Liberando o processo na memória.
    free(celulas[lista->primeiro].processo);
    celulas[lista->primeiro].processo = NULL;

    int tempPrimeiro = lista->primeiro;
    int tempPrimeiroProx = celulas[lista->primeiro].prox;

    // Apontando a célula deletada para a próxima célula disponível.
    celulas[lista->primeiro].ant = INICIO_DA_LISTA;
    celulas[lista->primeiro].prox = lista->celulasDisp;

    // Se a célula deletada não é a última.
    if (tempPrimeiroProx != FINAL_DA_LISTA)
    {
        // Tornando o próximo elemento início da lista.
        celulas[tempPrimeiroProx].ant = INICIO_DA_LISTA;
        lista->primeiro = tempPrimeiroProx;
    }

    lista->celulasDisp = tempPrimeiro;
    lista->numCelOcupados--;

    return true;
}


/*
 * Imprime a lista.
 *
 * @param    lista    ponteiro para a estrutura Lista.
 */
void imprimeData(Lista *lista)
{
    // Caso não haja nenhum elemento.
    if (tamanho(lista) == NENHUM_ELEMENTO)
    {
        printf(LISTA_VAZIA);
        return;
    }

    Celula *celulas = (Celula *) lista->celulas;
    int elementoAtual = lista->primeiro;

    // Iterando na lista.
    while (elementoAtual != FINAL_DA_LISTA)
    {
        printf(PRINT_ELEMENTO,
               elementoAtual, celulas[elementoAtual].processo->PID,
               celulas[elementoAtual].ant,
               celulas[elementoAtual].prox);

        elementoAtual = celulas[elementoAtual].prox;
    }
}


/*
 * Limpa a lista na memória.
 *
 * @param    lista    ponteiro para a estrutura Lista.
 */
void destroiLista(Lista *lista)
{
    Celula *celulas = (Celula *) lista->celulas;

    for (int i = VALOR_INICIAL; i < lista->tamanho; i++)
    {
        if (celulas[i].processo != NULL)
        {
            free(celulas[i].processo);
        }
    }

    free(lista->celulas);
}