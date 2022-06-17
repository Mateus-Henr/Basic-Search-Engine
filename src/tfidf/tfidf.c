#include <stdlib.h>
#include <string.h>

#include "tfidf.h"

TFIDF *initialiseTFIDF(char *word, int numDocs)
{
    TFIDF *tfidf = (TFIDF *) malloc(sizeof(TFIDF));

    tfidf->numDocs = numDocs;
    tfidf->totalDocWithTerm = 0;
    tfidf->word = (char *) malloc(strlen(word));
    strcpy(tfidf->word, word);
    tfidf->distinctTermInDocs = (int *) malloc(numDocs * sizeof(int));
    tfidf->numOccurrencesInDocs = (int *) malloc(numDocs * sizeof(int));

    for (int i = 0; i < numDocs; i++)
    {
        tfidf->distinctTermInDocs[i] = 0;
        tfidf->numOccurrencesInDocs[i] = 0;
    }

    return tfidf;
}