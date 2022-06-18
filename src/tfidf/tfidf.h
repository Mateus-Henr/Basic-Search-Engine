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

TFIDF *initialiseTFIDF(char *word, int numDocs);

void initialiseRelevance(Relevance *relevance, long ID, char *filename, double value);

void freeTFIDF(TFIDF *tfidf);