#include <stdlib.h>
#include <string.h>

#include "tfidf.h"
/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */

/*
 *  Initialises TFIDF struct with given and default values.
 *
 *  @param     tfidf       pointer to TFIDF struct.
 *  @param     word        word to check.
 *  @param     numDocs     quantity of documents.
 */
void initialiseTFIDF(TFIDF *tfidf, char *word, int numDocs)
{
    tfidf->numDocs = numDocs;
    tfidf->DocsWithTerm = 0;
    tfidf->word = (char *) malloc(strlen(word) + 1);
    strcpy(tfidf->word, word);
    tfidf->distinctTermsInDocs = (int *) calloc(numDocs, sizeof(int));
    tfidf->occurrencesInDocs = (int *) calloc(numDocs, sizeof(int));
}


/*
 *  Initialises Relevant struct with given values.
 *
 *  @param     relevance     pointer to Relevance struct.
 *  @param     ID            file's id.
 *  @param     filename      name of the file.
 *  @param     value         final calculus value.
 */
void initialiseRelevance(Relevance *relevance, long ID, char *filename, double value)
{
    relevance->ID = ID;
    relevance->filename = (char *) malloc(strlen(filename) + 1);
    strcpy(relevance->filename, filename);
    relevance->value = value;
}


/*
 *  Deallocates TFIDF struct from memory.
 *
 *  @param     tfidf     pointer to TFIDF struct.
 */
void freeTFIDF(TFIDF *tfidf)
{
    if (tfidf->word)
    {
        free(tfidf->word);
    }

    if (tfidf->distinctTermsInDocs)
    {
        free(tfidf->distinctTermsInDocs);
    }

    if (tfidf->occurrencesInDocs)
    {
        free(tfidf->occurrencesInDocs);
    }
}


/*
 *  Deallocates Relevance struct from memory.
 *
 *  @param     tfidf     pointer to Relevance struct.
 */
void freeRelevance(Relevance *relevance)
{
    if (relevance->filename)
    {
        free(relevance->filename);
    }
}