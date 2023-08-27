#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../include/core/core.h"

size_t FILE_SIZE = 0;
char *buffer = NULL;

char *filetobuffer(FILE *file){
    size_t i = 0;

    // Get the file length
    fseek(file, 0, SEEK_END);
    FILE_SIZE = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    printf("File size :- %ld bytes.\n", FILE_SIZE);
    buffer = (void *) malloc (FILE_SIZE);

    if(buffer == NULL){
        printf("Failed to create buffer to store the file\n");
        return NULL;
    }

    size_t byte_read = fread(buffer, 1, FILE_SIZE, file);   // keeps track of the byte read

    if(byte_read != FILE_SIZE){
        printf("Error reading file into buffer\n");
        free(buffer);
        return NULL;
    }

    return buffer;
}

// Useless function
char getcharfrombuffer(char *buffer, size_t index){
    int i = 0;

    if(index < 0) return ' ';

    if(index == 0) return buffer[0];

    while(i < index){
        if(i == index){
            return buffer[i];
        }
        i++;
    }
}

void freefilebuffer(){
    free(buffer);
}