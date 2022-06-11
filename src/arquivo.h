#include "lista.h"

/*
 * Funções abstratas relacionadas a arquivos.
 */

bool geraArquivo(unsigned int qtdOperacoes, unsigned int numArquivo, unsigned int tamanhoLista);

void arquivoOutput(char *nomeArquivo, double tempoGasto);

unsigned int lerArquivo(Lista *lista, char *nomeArquivo);