#ifndef CORE_H
#define CORE_H


#include <stdlib.h>
#include <stdio.h>

#define M_EOF "\0"
#define bufferSize 16

extern short int FILE_HAS_ENDED;

// @brief returns a word from a file stream
// @param file stream
char *getWord(FILE *file);

#endif