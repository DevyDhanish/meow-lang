#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdio.h>

extern size_t FILE_SIZE;
extern size_t REDUSED_SIZE;
extern char *_OP_PRECEDENCE;

// Reads the whole file and puts it in a buffer
// @param `FILE *file` file to be converted into buffer
// @returns the whole file as buffer does not removes white spaces
char *filetobuffer(FILE *file);

/*
    returns a single word from a buffer containing a single line
    I don't think i'm using this function anyware
*/
char getcharfrombuffer(char *buffer, size_t index);

/*
    `filetobuffer` reads the whole file and malloc memory to  `char *buffer` according to the size of the file
    this function frees the `char *buffer`
*/
void freefilebuffer();

#endif