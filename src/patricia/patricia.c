#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "patricia.h"


// Function prototype.

void insertionSort(Relevance *array, int n);


/*
 *  Initialises PATRICIA struct with default values;
 */
void initialisePATRICIA(PATRICIA *patricia)
{
    patricia->root = (TreeNodeType *) malloc(sizeof(TreeNodeType));
    patricia->root = NULL;
    patricia->size = 0;
}


/*
 *  Inserts externalNode into the PATRICIA tree.
 *
 *  @param     patricia       pointer to PATRICIA struct.
 *  @param     word           word to insertIntoHashtable.
 *  @param     documentID     document's ID.
 */
bool insertIntoTree(PATRICIA *patricia, char *word, int documentID)
{
    return insertTreeNode(&patricia->root, word, documentID);
}


/*
 *  Gets the PATRICIA tree's size.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 *  @return                 number of words in the tree.
 */
int getTreeSize(PATRICIA *patricia)
{
    return patricia->size;
}


/*
 *  Prints the PATRICIA tree out.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void printTree(PATRICIA *patricia)
{
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
 *  Deallocates structs that have been allocated dynamically.
 *
 *  @param     patricia     pointer to PATRICIA struct.
 */
void freeTree(PATRICIA *patricia)
{
    freeTreeNodes(patricia->root);
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