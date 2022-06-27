/*
 * TP1-AEDS2-UFV-Florestal
 * Mecanismo de Busca Básico
 *
 * João Victor Graciano Belfort de andrade-4694
 * Vitor Ribeiro Lacerda-4675
 * Mateus Henrique Vieira Figueiredo-4707
 */
#include <stdbool.h>
#include "patricia/patricia.h"
#include "hashtable/hashtable.h"

char **readFilenamesHashtable(Hashtable *hashtable, char *inputFilename, int *numFiles);

bool readFileIntoHashtable(Hashtable *hashtable, char *filename, int fileNumber);

char **readFilenamesPatricia(PATRICIA *tree, char *inputFilename, int *numFiles);

bool readFileIntoPatricia(PATRICIA *tree, char *filename, int fileNumber);

void reformatString(char *dest, char *src);

void freeFilenames(char **filenames, int numFiles);