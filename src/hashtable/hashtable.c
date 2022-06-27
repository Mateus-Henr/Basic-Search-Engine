#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stddef.h>

#include "hashtable.h"

// According to Grammarly the longest word that is actually used in the English language has 45 words.
#define MAXIMUM_WORD_LENGTH 45


// Function prototypes.

int *initialiseWeightsArray(void);

int getTwoPowerValueGreaterOrEqual(int number);

int getPreviousPrime(int number);

bool checkForPrimality(int numberToCheck);

int hash(Hashtable *hashtable, int value);

void insertionSort(Relevance *array, int n);


/*
 *  Initialises Hashtable struct.
 *
 *  @param     hashtable            pointer to Hashtable struct.
 *  @param     sizeSuggestion       suggestion of size for the array that backs the struct.
 */
void initialiseHashtable(Hashtable *hashtable, int sizeSuggestion)
{
    // Using Sedgewick way of finding best size for the hashtable array.
    hashtable->maxSize = getPreviousPrime(getTwoPowerValueGreaterOrEqual(sizeSuggestion));
    hashtable->linkedListArray = (LinkedList **) calloc(hashtable->maxSize, sizeof(LinkedList *));
    hashtable->weights = initialiseWeightsArray();
    hashtable->numInsertions = 0;
}


/*
 *  Initialises weight array that is used for generating hash codes.
 *  for words. It uses as default size the biggest word rarely used
 *  in the English language.
 *
 *  @return                        pointer to the initialised array.
 */
int *initialiseWeightsArray(void)
{
    srand(time(NULL));
    int *weights = (int *) malloc(MAXIMUM_WORD_LENGTH * sizeof(int));

    for (int i = 0; i < MAXIMUM_WORD_LENGTH; i++)
    {
        weights[i] = rand() % 1000 + 1;
    }

    return weights;
}


/*
 *  Gets the closest two power number greater or equal to a given number.
 *  Note: Used to find an M value according to Sedgewick.
 *
 *  @param     number     number to search for the two power.
 *  @return               closest number to the power of two greater or equal.
 */
int getTwoPowerValueGreaterOrEqual(int number)
{
    int twoPower = 0;

    while (pow(2, twoPower) < number)
    {
        twoPower++;
    }

    return (int) pow(2, twoPower);
}


/*
 *  Gets the closest previous prime of a given number.
 *  Note: Used to find an M value according to Sedgewick.
 *
 *  @param     number     number to search for the prime.
 *  @return               closest previous prime of a number.
 */
int getPreviousPrime(int number)
{
    while (!checkForPrimality(number))
    {
        number--;
    }

    return number;
}


/*
 *  Checks if a number is prime or not.
 *
 *  @param     numberToCheck     number to check its primality.
 *  @return                      whether the number is prime or not.
 */
bool checkForPrimality(int numberToCheck)
{
    for (int i = 2; i < sqrt(numberToCheck); i++)
    {
        if ((numberToCheck % i) == 0)
        {
            return false;
        }
    }

    return true;
}


/*
 *  Gets an index within the range of the hashtable array based on a hash code.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @param     value         hash code value.
 *  @return                  index for the hashtable array.
 */
int hash(Hashtable *hashtable, int value)
{
    return abs(value % hashtable->maxSize);
}


/*
 *  Inserts a new word into the hashtable.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @param     word          word to be inserted.
 *  @param     documentID    document's number (ID).
 *  @return                  whether the operation was successful or not.
 */
bool insertIntoHashtable(Hashtable *hashtable, const char *word, long documentID)
{
    int hashedKey = hash(hashtable, hashCode(word, hashtable->weights));

    if (!hashtable->linkedListArray[hashedKey])
    {
        hashtable->linkedListArray[hashedKey] = initialiseLinkedList();

        if (!hashtable->linkedListArray[hashedKey])
        {
            return false;
        }
    }

    if (!push(hashtable->linkedListArray[hashedKey], word, documentID))
    {
        return false;
    }

    hashtable->numInsertions++;

    return true;
}


/*
 *  Calculates TF-IDF and put result into TFIDF struct.
 *
 *  @param     list      pointer to LinkedList struct.
 *  @param     tfidf     pointer to TFIDF struct.
 */
void getTFIDFHashtable(Hashtable *hashtable, TFIDF *tfidf)
{
    for (int i = 0; i < hashtable->maxSize; i++)
    {
        if (hashtable->linkedListArray[i])
        {
            getTFIDFLinkedList(hashtable->linkedListArray[i], tfidf);
        }
    }
}


/*
 *  Checks if the hashtable is empty.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @return                  whether the hashtable is empty or not.
 */
bool isHashtableEmpty(Hashtable *hashtable)
{
    return hashtable->numInsertions == 0;
}


/*
 *  Sorts the hashtable by creating a linked list of pointers
 *  and then adding sorted items to it. After that this list gets
 *  printed out and deleted at the end.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 */
void sortAndPrintHashtable(Hashtable *hashtable)
{
    if (isHashtableEmpty(hashtable))
    {
        printf("\nEMPTY.\n");
        return;
    }

    LinkedList *list = initialiseLinkedList();

    for (int i = 0; i < hashtable->maxSize; i++)
    {
        if (hashtable->linkedListArray[i])
        {
            struct Node *currNode = hashtable->linkedListArray[i]->head;

            while (currNode)
            {
                pushSorted(list, currNode);
                currNode = currNode->next;
            }
        }
    }

    printLinkedList(list);
    freeSortedLinkedList(list);
}


/*
 *  Calculates TD-IDF weight of a given word.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @param     weights       pointer to the weights array.
 *  @param     tfidf         pointer to TFIDF struct.
 */
void calculateWeightHashtable(Hashtable *hashtable, double *weights, TFIDF *tfidf)
{
    getTFIDFHashtable(hashtable, tfidf);

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
 *  @param     hashtable     pointer to Hashtable struct.
 *  @param     words         array containing the words.
 *  @param     filenames     array containing the filenames.
 *  @param     numWords      number of words in the array.
 *  @param     numDocs       number of files.
 */
void relevanceHashtable(Hashtable *hashtable, char **words, char **filenames, int numWords, int numDocs)
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
        calculateWeightHashtable(hashtable, weights, &tfidf);

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

    printf("\nHashtable TD-IDF:\n");
    for (int i = 0; i < numDocs; i++)
    {
        printf("Texto %ld (%s) = %lf\n", relevanceArray[i].ID, relevanceArray[i].filename, relevanceArray[i].value);
        freeRelevance(&relevanceArray[i]);
    }
    printf("\n");
}


/*
 *  Performs the insertion sort on an array.
 *
 *  @param     array     pointer to array of type Relevance to be sorted.
 *  @param     n         array's size.
 */
void insertionSort(Relevance *array, int n)
{
    for (int i = 1; i < n; i++)
    {
        Relevance key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j].value < key.value)
        {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}


/*
 *  Gets the sizeof of a hashtable.
 *
 *  @param     hashtable    pointer to Hashtable struct.
 *  @return                 size of the hashtable in bytes.
 */
long getSizeOfHashtable(Hashtable *hashtable)
{
    long size = 0;

    if (hashtable->linkedListArray)
    {
        for (int i = 0; i < hashtable->maxSize; i++)
        {
            if (hashtable->linkedListArray[i])
            {
                size += getSizeOfLinkedList(hashtable->linkedListArray[i]);
            }

            size += sizeof(LinkedList *);
        }
    }

    if (hashtable->weights)
    {
        size += sizeof(int) * MAXIMUM_WORD_LENGTH;
    }

    size += sizeof(Hashtable);

    return size;
}


/*
 *  Deallocates structs that have been allocated dynamically.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 */
void freeHashtable(Hashtable *hashtable)
{
    if (hashtable->linkedListArray)
    {
        for (int i = 0; i < hashtable->maxSize; i++)
        {
            if (hashtable->linkedListArray[i])
            {
                freeLinkedList(hashtable->linkedListArray[i]);
            }
        }

        free(hashtable->linkedListArray);
    }

    if (hashtable->weights)
    {
        free(hashtable->weights);
    }
}