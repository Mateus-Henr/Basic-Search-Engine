/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

typedef struct
{
    char *word;
    int *distinctTermsInDocs;
    int *occurrencesInDocs;
    int numDocs;
    int DocsWithTerm;
} TFIDF;

typedef struct
{
    long ID;
    char *filename;
    double value;
} Relevance;

void initialiseTFIDF(TFIDF *tfidf, char *word, int numDocs);

void initialiseRelevance(Relevance *relevance, long ID, char *filename, double value);

void freeTFIDF(TFIDF *tfidf);

void freeRelevance(Relevance *relevance);