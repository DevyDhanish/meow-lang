#ifndef CORE_H
#define CORE_H


#include <stdlib.h>
#include <stdio.h>

#include "../DS/ll/ll.h"

#define bufferSize 16

extern short int FILE_HAS_ENDED;

// @brief Reads a line from given file stream
// @param file stream ` *file `
// @returns a pointer pointing to a array of characters (a line)
char *readLine(FILE *file);

// @brief reads a word from a file stream
// @param file stream to read from
// @return returns null terminated word
char *getWord(char *file);

size_t getFileLength(FILE *file);

char *removeWhitespaceFromFile(FILE *file);

#endif