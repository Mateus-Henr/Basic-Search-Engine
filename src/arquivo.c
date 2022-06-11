#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arquivo.h"

#define CEM 100
#define UM 1
#define DOIS 2
#define LIMITE_NUMERO_ARQUIVO 99
#define VALOR_INICIAL 0
#define NOME_ARQUIVO_USUARIO "..//arquivos//%s.txt"
#define NOME_ARQUIVO_USUARIO_SAIDA "..//arquivos//%s-saida.txt"
#define TAMANHO_STRING_ARQUIVO 31
#define NAO_ENCONTRADO "\nO arquivo com nome '%s' não pode ser encontrado.\n"
#define ERRO_FORMATO "\nErro de formato. Tenha certeza que o arquivo segue o formato especificado.\n"
#define NOME_ARQUIVO "..//Arquivos//teste%02d.txt"
#define ERRO_CRIAR_ARQUIVO "\nErro ao tentar criar arquivo.\n"
#define NUMERO_INVALIDO "Número inválido. Deve ser entre 0 e 99"


/*
 * Esse método é utilizado para gerar um arquivo customizado pelo usuário. Ele irá receber informações para incluir
 * dentro de um arquivo com nome "testeNN" onde "NN" é um número especificado pelo usuário.
 * Como explicado anteriormente o número tem que seguir o formato "NN", ou seja, só números de 2 algarismos são válidos.
 */
bool geraArquivo(unsigned int qtdOperacoes, unsigned int numArquivo, unsigned int tamanhoLista)
{
    // Checando se o número informado pelo usuário é válido.
    if (numArquivo > LIMITE_NUMERO_ARQUIVO)
    {
        printf(NUMERO_INVALIDO);
        return false;
    }

    char nome_arquivo[TAMANHO_STRING_ARQUIVO];
    FILE *pArquivo;

    // Criando "seed" para o "rand()" método para tornar a ordem da geração de números aleatória.
    srand(time(NULL));
    sprintf(nome_arquivo, NOME_ARQUIVO, numArquivo); // Criando caminho para o pArquivo.
    pArquivo = fopen(nome_arquivo, "w"); // Criando e abrindo o pArquivo para colocar as informações.

    // Caso ocorra um erro ao tentar criar o pArquivo.
    if (!pArquivo)
    {
        printf(ERRO_CRIAR_ARQUIVO);
        return false;
    }

    // Escrevendo dados informados pelo usuário.
    fprintf(pArquivo, "%d", tamanhoLista);
    fprintf(pArquivo, "%s", "\n");
    fprintf(pArquivo, "%d", qtdOperacoes);
    fprintf(pArquivo, "%s", "\n");

    // Escrevendo escolha de operações (inserção ou remoção) e a quantidade que as mesmas serão utilizadas de forma
    // aleatória.
    for (int j = 0; j < qtdOperacoes; j++)
    {
        fprintf(pArquivo, "%d", rand() % DOIS);
        fprintf(pArquivo, "%s", " ");
        fprintf(pArquivo, "%d", rand() % CEM);
        if (j != (qtdOperacoes - UM))
        {
            fprintf(pArquivo, "%s", "\n");
        }
    }

    fclose(pArquivo);
    pArquivo = NULL;

    return true;
}


/*
 * Essa função é utilizada para gerar um arquivo externo no formato "nome_do_arquivo-saida.txt" com os dados:
 * nome do arquivo e o tempo gasto.
 */
void arquivoOutput(char *nomeArquivo, double tempoGasto)
{
    FILE *arquivo;
    char caminho_arquivo[CHAR_MAX];

    sprintf(caminho_arquivo, NOME_ARQUIVO_USUARIO_SAIDA, nomeArquivo);
    arquivo = fopen(caminho_arquivo, "w");

    fprintf(arquivo, "<< %s >>", nomeArquivo);
    fprintf(arquivo, " Tempo gasto em segundos: %0.2lf", tempoGasto);

    fclose(arquivo);
}


/*
 * O método seguinte foi criado com o intuito de ler data de um arquivo em que o nome será passado pelo usuário.
 * Esse método lerá um arquivo seguindo um formato estrito. O mesmo irá criar uma lista onde irá realizar operações
 * sobre. Tem como retorno o ponteiro da lista onde foram realizadas as operações especificadas no arquivo.
 * Retorna um unsigned int para in informar se o metódo foi executado com sucesso.
*/
unsigned int lerArquivo(Lista *lista, char *nomeArquivo)
{
    unsigned int numOperacoes;
    unsigned int tamanhoLista;
    char pathArquivo[CHAR_MAX];
    FILE *arquivo;

    // Criando caminho para o arquivo. É importante lembrar que devido o uso de uma constante para ler o arquivo
    // informado pelo usuário o mesmo deve estar dentro da pasta "Arquivos" deste projeto.
    sprintf(pathArquivo, NOME_ARQUIVO_USUARIO, nomeArquivo);
    arquivo = fopen(pathArquivo, "r"); // Abrindo o arquivo para leitura.

    // Condição para caso não encontre o arquivo especificado.
    if (!arquivo)
    {
        printf(NAO_ENCONTRADO, nomeArquivo);
        return 0;
    }

    // Lendo o tamanho da lista (1° dado). Lidando com valores inválidos.
    if (!fscanf(arquivo, "%i", &tamanhoLista))
    {
        printf(ERRO_FORMATO);
        return 0;
    }

    // Lendo o número de operações (inserções e/ou remoções). Lidando com valores inválidos.
    if (!fscanf(arquivo, "%i", &numOperacoes))
    {
        printf(ERRO_FORMATO);
        return 0;
    }

    inicializaLista(lista, tamanhoLista);

    // Criando loop para realizar a quantidade de operações da opção escolhida pelo usuário.
    for (int i = VALOR_INICIAL; i < numOperacoes; i++)
    {
        unsigned int operacao;
        unsigned int qtdOperacao;

        if (!fscanf(arquivo, "%i %i", &operacao, &qtdOperacao))
        {
            printf(ERRO_FORMATO);
            return 0;
        }

        for (int j = VALOR_INICIAL; j < qtdOperacao; j++)
        {
            operacao ? removeFrente(lista) : insereOrdenado(lista);
        }
    }

    fclose(arquivo);

    return 1;
}