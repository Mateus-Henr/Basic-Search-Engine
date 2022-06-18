#include <stdlib.h>
#include <string.h>

#include "tfidf.h"


/*
 *  Initialises TFIDF struct with given and default values.
 *
 *  @param     word        word to check.
 *  @param     numDocs     quantity of documents.
 *  @return                pointer to the initialised struct.
 */
TFIDF *initialiseTFIDF(char *word, int numDocs)
{
    TFIDF *tfidf = (TFIDF *) malloc(sizeof(TFIDF));

    tfidf->numDocs = numDocs;
    tfidf->DocsWithTerm = 0;
    tfidf->word = (char *) malloc(strlen(word) + 1);
    strcpy(tfidf->word, word);
    tfidf->distinctTermsInDocs = (int *) calloc(numDocs, sizeof(int));
    tfidf->occurrencesInDocs = (int *) calloc(numDocs, sizeof(int));

    return tfidf;
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
    if (tfidf)
    {
        if (tfidf->word)
        {
            free(tfidf->word);
        }

        free(tfidf);
    }
}