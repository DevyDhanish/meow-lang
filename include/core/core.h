#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdio.h>

extern size_t FILE_SIZE;

// Reads the whole file and puts it in a buffer
// @param `FILE *file` file to be converted into buffer
// @returns the whole file as buffer does not removes white spaces
char *filetobuffer(FILE *file);

char getcharfrombuffer(char *buffer, size_t index);

#endif