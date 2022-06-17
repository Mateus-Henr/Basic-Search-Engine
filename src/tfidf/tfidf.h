typedef struct
{
    char *word;
    int *distinctTermInDocs;
    int *numOccurrencesInDocs;
    int numDocs;
    int totalDocWithTerm;
} TFIDF;

TFIDF *initialiseTFIDF(char *word, int numDocs);