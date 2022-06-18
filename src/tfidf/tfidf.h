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