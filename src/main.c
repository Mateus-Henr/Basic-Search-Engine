#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "arquivo.h"

#define UM 1
#define ZERO 0
#define EXIT 0
#define VALOR_INICIAL 0
#define INVALIDO -1
#define PRIMEIRA_OPCAO 1
#define SEGUNDA_OPCAO 2
#define MOSTRAR_OPCOES 3
#define VALOR_INVALIDO "\nValor Invalido\n"
#define OPCAO_INVALIDA "\nOpcao Invalida\n"
#define LISTA_CHEIA "\nLista cheia!\n"
#define LISTA_VAZIA "\nLista Vazia!\n"


// Mencionando funções

void mostrarOpcoes(void);

double inicializaRelogio(void);

double finalizaRelogio(double tempoInicial);

void limparStdin();


/*
 * Método principal que gera uma aplicação interativa com o usuário para mostrar o usuário as opções e lidar
 * com valores inválidos.
 */
int main(void)
{
    bool loop = true;
    int imprime_lista = INVALIDO;

    // Usando loop para lidar com input inválidos e repetições.
    while (loop)
    {
        int escolha;

        printf("\n\nSimulador de sistema de gerenciamento de processos");
        printf("\nDigite a opcao:");
        mostrarOpcoes(); // Mostrando opções.
        if (!scanf("%d", &escolha)) // Recebendo escolha do usuário e lidando com valores inválidos.
        {
            printf(OPCAO_INVALIDA);
            limparStdin();
            continue;
        }

        // Usando switch conforme a opção que o usuário escolheu.
        switch (escolha)
        {
            case EXIT: // Opção 0 (sair)
                printf("\nBye :(\n");
                loop = false;
                break;
            case PRIMEIRA_OPCAO: // Opção 1 (Arquivo).
                printf("\nInformacoes de arquivo");
                printf("\n[1] Criar\n[2] Ler Arquivo\n");

                int opcao;
                if (!scanf("%d", &opcao))
                {
                    printf(OPCAO_INVALIDA);
                    limparStdin();
                    break;
                }

                // Opcão para criar arquivo.
                if (opcao == PRIMEIRA_OPCAO)
                {
                    // Definido variáveis.
                    int qtd_operacoes;
                    int num_arquivo;
                    int tamanho_lista;

                    // --------------- Recebendo valores e checando se os mesmos são inválidos -------------------------
                    printf("\nDigite o numero do arquivo que deseja criar:\n");
                    if (!scanf("%d", &num_arquivo) || num_arquivo < ZERO)
                    {
                        printf(OPCAO_INVALIDA);
                        limparStdin();
                        break;
                    }

                    printf("\nDigite o tamanho da lista para o arquivo:\n");
                    if (!scanf("%d", &tamanho_lista) || tamanho_lista < ZERO)
                    {
                        printf(OPCAO_INVALIDA);
                        limparStdin();
                        break;
                    }

                    printf("\nDigite a quantidade de operacoes:\n");
                    if (!scanf("%d", &qtd_operacoes) || qtd_operacoes < ZERO)
                    {
                        printf(OPCAO_INVALIDA);
                        limparStdin();
                        break;
                    }
                    // -------------------------------------------------------------------------------------------------

                    // --------------------------------- Gerando arquivo -----------------------------------------------
                    if (geraArquivo(qtd_operacoes, num_arquivo, tamanho_lista))
                    {
                        printf("\nArquivo com nome 'teste%02d.txt' gerado!\n", num_arquivo);
                    }
                    // -------------------------------------------------------------------------------------------------
                }
                else if (opcao == SEGUNDA_OPCAO)
                {
                    // Definido variáveis.
                    char nome_arquivo[CHAR_MAX];

                    // ------------------------------ Lendo arquivo ----------------------------------------------------
                    printf("\nDigite o nome do arquivo (sem a extensao):\n");
                    scanf("%s", nome_arquivo);

                    // Inicializando clock.
                    double tempo_inicial = inicializaRelogio();

                    // Inicializando lista que será usada para receber informações do arquivo.
                    Lista lista;

                    // Checando se ouve algum problem durante a leitura do arquivo.
                    if (!lerArquivo(&lista, nome_arquivo))
                    {
                        limparStdin();
                        break;
                    }

                    // Parando clock e calculando o tempo gasto.
                    double tempo_gasto = finalizaRelogio(tempo_inicial);
                    // -------------------------------------------------------------------------------------------------

                    // ---------------- Mostrando Informações sobre a lista gerada pelo arquivo -----------------------
                    printf("\nTempo em segundos: %0.2lf\n ", tempo_gasto);
                    arquivoOutput(nome_arquivo, tempo_gasto); // Gerando arquivo de saída.

                    // Perguntando o usuário se ele deseja ver o conteúdo da lista.
                    printf("\nDeseja imprimir o conteudo da lista?\n[1] Sim [0] Nao\n");
                    if (!scanf("%d", &imprime_lista))
                    {
                        printf(VALOR_INVALIDO);
                        limparStdin();
                        break;
                    }

                    // Opção para o usuário decidir se ele deseja printar a lista.
                    if (imprime_lista)
                    {
                        imprimeData(&lista);
                    }

                    destroiLista(&lista);
                    // -------------------------------------------------------------------------------------------------
                }
                else // Caso a opção for inválida.
                {
                    printf(OPCAO_INVALIDA);
                    limparStdin();
                    break;
                }
                break;
            case SEGUNDA_OPCAO: // Opção 2 (valores vindos do usuário)
                // --------------------- Recebendo valores do usuário e aplicando eles na lista ------------------------
                printf("\nInsercao de valores pelo usuario\n");

                int tamanho_lista;
                // Recebendo tamanho da lista e lidando com valores inválidos.
                printf("\nDigite o tamanho da lista: \n");
                if (!scanf("%d", &tamanho_lista) || tamanho_lista < ZERO)
                {
                    printf(VALOR_INVALIDO);
                    limparStdin();
                    break;
                }

                // Inicializando lista.
                Lista lista;
                inicializaLista(&lista, tamanho_lista);

                // Variável "flag" para o loop.
                int continuar = 1;

                // Loop para receber múltiplos valores de remoção ou inserção.
                while (continuar)
                {
                    int insere_ou_remove;
                    int qtd_operacoes;

                    // Recebendo a escolha do usuário (remoção ou inserção) e lidando com valores inválios.
                    printf("\n[0] Insercoes  [1] Remocoes:\n ");
                    if (!scanf("%d", &insere_ou_remove))
                    {
                        printf(VALOR_INVALIDO);
                        limparStdin();
                        continue;
                    }

                    // Opção se o usuário escolher inserção.
                    if (insere_ou_remove == ZERO)
                    {
                        printf("\nQuantidade de insercoes:\n ");
                        if (!scanf("%d", &qtd_operacoes) || qtd_operacoes < ZERO)
                        {
                            printf(VALOR_INVALIDO);
                            limparStdin();
                            continue;
                        }

                        double tempo_inicial = inicializaRelogio();

                        // Usado para detectar se a lista estiver cheia após a realização da operação.
                        unsigned int qtd_insercoes = ZERO;

                        for (int i = VALOR_INICIAL; i < qtd_operacoes; i++)
                        {
                            if (insereOrdenado(&lista))
                            {
                                qtd_insercoes++;
                            }
                        }

                        // Checando se a lista está cheia baseado no valor da última operação.
                        if (qtd_insercoes != qtd_operacoes)
                        {
                            printf(LISTA_CHEIA);
                        }

                        printf("\n%d insercoes concluidas com sucesso.\n", qtd_insercoes);
                        printf("\nTempo em segundos: %0.2lf\n ", finalizaRelogio(tempo_inicial));

                        printf("\nDeseja imprimir o conteudo da lista?\n[1] Sim [0] Nao\n");
                        if (!scanf("%d", &imprime_lista))
                        {
                            printf(VALOR_INVALIDO);
                            limparStdin();
                            continue;
                        }

                        if (imprime_lista)
                        {
                            imprimeData(&lista);
                        }
                    }
                    else if (insere_ou_remove == UM) // Opção se o usuário escolher remoção.
                    {
                        printf("\nQuantidade de remocoes:\n ");
                        if (!scanf("%d", &qtd_operacoes) || qtd_operacoes < ZERO)
                        {
                            printf(VALOR_INVALIDO);
                            limparStdin();
                            continue;
                        }

                        double tempo_inicial = inicializaRelogio();

                        // Usado para detectar se a lista estiver vazia após a realização da operação.
                        unsigned int qtd_remocoes = ZERO;

                        for (int i = VALOR_INICIAL; i < qtd_operacoes; i++)
                        {
                            if (removeFrente(&lista))
                            {
                                qtd_remocoes++;
                            }
                        }

                        // Checando se a lista está vazia baseado no valor da última operação.
                        if (qtd_remocoes != qtd_operacoes)
                        {
                            printf(LISTA_VAZIA);
                        }

                        printf("\n%d remocoes concluidas com sucesso.\n", qtd_remocoes);
                        printf("\nTempo em segundos: %0.2lf\n ", finalizaRelogio(tempo_inicial));

                        // Perguntando se o usuário deseja imprimir conteúdo da lista.
                        printf("\nDeseja imprimir o conteudo da lista?\n[1] Sim [0] Nao\n");
                        if (!scanf("%d", &imprime_lista)) // Checando se o valor é inválido.
                        {
                            printf(VALOR_INVALIDO);
                            limparStdin();
                            continue;
                        }

                        if (imprime_lista)
                        {
                            imprimeData(&lista);
                        }
                    }
                    else
                    {
                        printf(OPCAO_INVALIDA);
                        limparStdin();
                        continue;
                    }

                    // Recebendo escolha do usuário para decidir se ele quer realizar mais operações.
                    printf("\nAdicionar mais insersoes ou remocoes?\n");
                    printf("\n[1] Sim [0] Nao\n");
                    if (!scanf("%d", &continuar)) // Checando se o valor digitado é valido.
                    {
                        printf(OPCAO_INVALIDA);
                        limparStdin();
                    }

                    if (continuar != UM) // Continuar o loop.
                    {
                        printf(OPCAO_INVALIDA);
                        continuar = UM;
                        limparStdin();
                    }
                }
                destroiLista(&lista);
                // -----------------------------------------------------------------------------------------------------
                break;
            case MOSTRAR_OPCOES: // Opção 3 (mostrar opções).
                mostrarOpcoes();
                break;
            default: // Valor inválido do usuário.
                printf(OPCAO_INVALIDA);
                limparStdin();
                break;
        }
    }

    return ZERO;
}


/*
 * Descreve as opções que o usuário pode escolher, por meio do console.
 */
void mostrarOpcoes(void)
{
    printf("\n0 - Sair"
           "\n1 - Arquivo"
           "\n2 - Digitar valores para teste"
           "\n3 - Mostrar opcoes\n");
}


/*
 * Limpa o "stdin" para evitar problemas com "scanf()" dentro de loops.
 */
void limparStdin(void)
{
    int c = getchar();

    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}


/*
 * Inicia o clock.
 *
 * @return      valor do clock.
 */
double inicializaRelogio(void)
{
    return clock();
}


/*
 * Finaliza o clock e calcula o tempo total.
 *
 * @param       tempoInicial        valor inicial do clock.
 * @return                          tempo total.
 */
double finalizaRelogio(double tempoInicial)
{
    return (clock() - tempoInicial) / CLOCKS_PER_SEC;
}