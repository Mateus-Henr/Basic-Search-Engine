#include <stdlib.h>
#include <time.h>

#include "processo.h"

#define UM 1
#define LIMITE 5


/*
 * Inicializa um processo com PID (inteiro) e prioridade (inteiro entre 1 e 5) aleatórios,
 * além de conter o tempo de criação (retirado da máquina do usuário).
 *
 * @return          ponteiro para processo criado na memória.
 */
TProcesso *inicializa_processo(void)
{
    TProcesso *processo = (TProcesso *) malloc(sizeof *processo);
    processo->PID = UM + rand();
    processo->prioridade = UM + (rand() % LIMITE);
    inicializa_tempo(processo);

    return processo;
}


/*
 * Inicializa a hora de criação do processo tendo como base o horário na máquina do usuário.
 *
 * @param       processo       ponteiro para a estrutura Processo.
 */
void inicializa_tempo(TProcesso *processo)
{
    time_t hora_cru;
    struct tm *hora_atual;

    time(&hora_cru);
    hora_atual = localtime(&hora_cru);
    processo->hora = hora_atual;
}


/*
 * ‘Getter’ de ID.
 *
 * @param       processo       ponteiro para a estrutura Processo.
 * @return                     valor do PID do processo.
 */
unsigned int get_PID(TProcesso *processo)
{
    return processo->PID;
}


/*
 * ‘Setter’ de ID.
 *
 * @param       processo       ponteiro para a estrutura Processo.
 * @param       novoPID        novo valor para o PID do processo.
 */
void setPID(TProcesso *processo, unsigned int novoPID)
{
    processo->PID = novoPID;
}


/*
 * ‘Getter’ de prioridade.
 *
 * @param       processo       ponteiro para a estrutura Processo.
 * @return                     valor da prioridade do processo.
 */
unsigned int getPrioridade(TProcesso *processo)
{
    return processo->prioridade;
}


/*
 * ‘Setter’ de prioridade.
 *
 * @param       processo             ponteiro para a estrutura Processo.
 * @param       novaPrioridade       novo valor para a prioridade do processo.
 */
void setPrioridade(TProcesso *processo, unsigned int novaPrioridade)
{
    processo->prioridade = novaPrioridade;
}


/*
 * ‘Getter’ de hora de criação. Usada função "asctime()" da biblioteca "time.h" com formato "Www Mmm dd hh:mm:ss yyyy".
 *
 * @param       processo       ponteiro para a estrutura Processo.
 * @return                     hora de criação do processo.
 */
char *get_hora(TProcesso *processo)
{
    return asctime(processo->hora);
}