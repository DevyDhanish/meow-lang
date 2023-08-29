#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../../include/core/core.h"

size_t FILE_SIZE = 0;
size_t REDUSED_SIZE = 0;
char *buffer = NULL;

char *filetobuffer(FILE *file){

    // Get the file length
    fseek(file, 0, SEEK_END);
    FILE_SIZE = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    char *buffer = (char *)malloc(FILE_SIZE * sizeof(char));
    if(buffer == NULL){
        printf("Failed to create buffer to store the file\n");
        return NULL;
    }

    int counter = 0;
    char ch;

    while ((ch = getc(file)) != EOF) {
        if (ch != '\n') {
            buffer[counter] = ch;
            counter++;
        }
    }

    REDUSED_SIZE = counter + 1;

    printf("File size :- %ld bytes.\n", FILE_SIZE);
    printf("Redused size :- %ld bytes\n", REDUSED_SIZE);

    fclose(file);

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