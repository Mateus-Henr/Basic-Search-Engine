/*
 * ----- Estrutura abstrata para representação de um processo. -----
 * Essa estrutura conta com um ID de processo "PID" (inteiro gerado aleatoriamente), uma prioridade (inteiro entre
 * 1 e 5 gerado aleatoriamente) e um tempo de criação (retirado do computador do usuário, para tal funcionalidade
 * a biblioteca "time.h" está sendo utilizada).
 */

typedef struct Processo
{
    unsigned int PID;
    unsigned int prioridade;
    struct tm *hora;
} TProcesso;


// Funções de inicialização

TProcesso *inicializa_processo();

void inicializa_tempo(TProcesso *processo);


// Getters e Setters

unsigned int get_PID(TProcesso *processo);

void setPID(TProcesso *processo, unsigned int novoPID);

unsigned int getPrioridade(TProcesso *processo);

void setPrioridade(TProcesso *processo, unsigned int novaPrioridade);

char *get_hora(TProcesso *processo);