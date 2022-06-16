#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stddef.h>

#include "hashtable.h"

// According to Grammarly the longest word that is actually used in the English language has 45 words.
#define MAXIMUM_WORD_LENGTH 45


// Function prototypes.
int hash(Hashtable *hashtable, int value);

int *initialiseWeightsArray();

int getTwoPowerValueGreaterOrEqual(int number);

int getPreviousPrime(int number);

bool checkForPrimality(int numberToCheck);


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
    hashtable->linkedListsArray = (LinkedList **) malloc(sizeof(LinkedList *) * hashtable->maxSize);

    for (int i = 0; i < hashtable->maxSize; i++)
    {
        hashtable->linkedListsArray[i] = NULL;
    }

    hashtable->weights = initialiseWeightsArray(45);
    hashtable->numberOfElements = 0;
}


/*
 *  Initialises weight array that is used for generating hash codes.
 *  for words.
 *
 *  @param     numberOfElements    array's size.
 *  @return                        pointer to the initialised array.
 */
int *initialiseWeightsArray()
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
 *  Gets the two power greater or equal to a given number.
 *  Note: Used to find an M value according to Sedgewick.
 *
 *  @param     number     number to search for the two power.
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
 *  Inserts a new word into the hashtable.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @param     word          word to be inserted.
 *  @param     documentID    document's number (ID).
 *  @return                  whether the operation was successful or not.
 */
bool insert(Hashtable *hashtable, const char *word, long documentID)
{
    int hashedKey = hash(hashtable, hashCode(word, hashtable->weights));

    if (!hashtable->linkedListsArray[hashedKey])
    {
        hashtable->linkedListsArray[hashedKey] = initialiseLinkedList();

        if (!hashtable->linkedListsArray[hashedKey])
        {
            return false;
        }
    }

    if (!push(hashtable->linkedListsArray[hashedKey], word, documentID))
    {
        return false;
    }

    hashtable->numberOfElements++;

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
 *  Gets the hashtable size.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @return                  hashtable size.
 */
int getHashtableSize(Hashtable *hashtable)
{
    return hashtable->numberOfElements;
}


/*
 *  Checks if the hashtable is empty.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 *  @return                  whether the hashtable is empty or not.
 */
bool isHashtableEmpty(Hashtable *hashtable)
{
    return hashtable->numberOfElements == 0;
}


/*
 *  Prints the hashtable out.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 */
void printHashtable(Hashtable *hashtable)
{
    if (isHashtableEmpty(hashtable))
    {
        printf("EMPTY.\n");
        return;
    }

    for (int i = 0; i < hashtable->maxSize; i++)
    {
        if (!hashtable->linkedListsArray[i])
        {
            printf("[%d] NULL\n", i);
        }
        else
        {
            printf("[%d] ", i);
            printLinkedList(hashtable->linkedListsArray[i]);
        }
    }
}


/*
 *  Sorts and then prints the hashtable out.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 */
void sortAndPrintHashtable(Hashtable *hashtable)
{
    if (isHashtableEmpty(hashtable))
    {
        printf("EMPTY.\n");
        return;
    }

    LinkedList *list = initialiseLinkedList();

    for (int i = 0; i < hashtable->maxSize; i++)
    {
        if (hashtable->linkedListsArray[i])
        {
            struct Node *currNode = hashtable->linkedListsArray[i]->head;

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
 *  Deallocates structs that have been allocated dynamically.
 *
 *  @param     hashtable     pointer to Hashtable struct.
 */
void freeHashtable(Hashtable *hashtable)
{
    if (hashtable->linkedListsArray)
    {
        for (int i = 0; i < hashtable->maxSize; i++)
        {
            if (hashtable->linkedListsArray[i])
            {
                freeLinkedList(hashtable->linkedListsArray[i]);
            }
        }

        free(hashtable->linkedListsArray);
    }

    if (hashtable->weights)
    {
        free(hashtable->weights);
    }
}