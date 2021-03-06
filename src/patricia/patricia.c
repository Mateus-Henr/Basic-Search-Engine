/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "patricia.h"

// Function prototype.

void insertionSort(Relevance *array, int n);


/*
 *  Initialises PATRICIA struct with default values.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void initialisePATRICIA(PATRICIA *patricia)
{
    patricia->root = (TreeNodeType *) malloc(sizeof(TreeNodeType));
    patricia->root = NULL;
}


/*
 *  Inserts externalNode into the PATRICIA tree.
 *
 *  @param     patricia       pointer to PATRICIA struct.
 *  @param     word           word to insertIntoHashtable.
 *  @param     documentID     document's ID.
 *  @return                   whether the operation was successful or not.
 */
bool insertIntoTree(PATRICIA *patricia, char *word, int documentID)
{
    return insertTreeNode(&patricia->root, word, documentID);
}


/*
 *  Prints the PATRICIA tree out.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void printTree(PATRICIA *patricia)
{
    if (!patricia->root)
    {
        printf("\nEMPTY.\n");
        return;
    }

    printTreeNode(patricia->root);
}


/*
 *  Gets TFIDF calculus in the PATRICIA tree.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 *  @param     tfidf        pointer to TFIDF struct.
 */
void getTFIDFPATRICIA(PATRICIA *patricia, TFIDF *tfidf)
{
    getTFIDFTreeNodes(patricia->root, tfidf);
}


/*
 *  Calculates TD-IDF weight of a given word.
 *
 *  @param     patricia      pointer to PATRICIA struct.
 *  @param     tfidf         pointer to TFIDF struct.
 */
void calculateWeightPATRICIA(PATRICIA *patricia, double *weights, TFIDF *tfidf)
{
    getTFIDFPATRICIA(patricia, tfidf);

    for (int i = 0; i < tfidf->numDocs; i++)
    {
        weights[i] = 0;

        if (tfidf->DocsWithTerm != 0)
        {
            weights[i] = (double) tfidf->occurrencesInDocs[i] * log(tfidf->numDocs) / (double) tfidf->DocsWithTerm;
        }
    }
}


/*
 *  Calculates the relevance of a term based on the TF-IDF calculus.
 *
 *  @param     tree          pointer to PATRICIA struct.
 *  @param     words         array containing the words.
 *  @param     filenames     array containing the filenames.
 *  @param     numWords      number of words in the array.
 *  @param     numDocs       number of files.
 */
void relevancePATRICIA(PATRICIA *tree, char **words, char **filenames, int numWords, int numDocs)
{
    Relevance relevanceArray[numDocs];
    double values[numDocs];
    int distinctTerms[numDocs];

    for (int i = 0; i < numDocs; i++)
    {
        values[i] = 0;
    }

    for (int i = 0; i < numWords; i++)
    {
        TFIDF tfidf;
        initialiseTFIDF(&tfidf, words[i], numDocs);

        double weights[tfidf.numDocs];
        calculateWeightPATRICIA(tree, weights, &tfidf);

        for (int j = 0; j < numDocs; j++)
        {
            distinctTerms[j] = tfidf.distinctTermsInDocs[j];
            values[j] += weights[j];
        }

        freeTFIDF(&tfidf);
    }

    for (int i = 0; i < numDocs; i++)
    {
        values[i] = (1.0 / (double) distinctTerms[i]) * values[i];
        initialiseRelevance(&relevanceArray[i], i + 1, filenames[i], values[i]);
    }

    insertionSort(relevanceArray, numDocs);

    printf("\nPATRICIA TD-IDF:\n");
    for (int i = 0; i < numDocs; i++)
    {
        printf("Texto %ld (%s) = %lf\n", relevanceArray[i].ID, relevanceArray[i].filename, relevanceArray[i].value);
        freeRelevance(&relevanceArray[i]);
    }
    printf("\n");
}


/*
 *  Gets the size of the PATRICIA tree.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 *  @return                 size of PATRICIA tree.
 */
long getSizeOfPATRICIA(PATRICIA *patricia)
{
    long size = 0;

    getSizeTreeNodes(patricia->root, &size);

    return size;
}


/*
 *  Deallocates structs that have been allocated dynamically.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void freeTree(PATRICIA *patricia)
{
    if (patricia->root)
    {
        freeTreeNodes(patricia->root);
        free(patricia->root);
    }
}
