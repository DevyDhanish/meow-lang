#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/core/core.h"
#include "../include/DS/list.h"
#include "../include/lexer/lexer.h"

FILE *fileptr;
char *fileBuffer;

int main(int argc, char **argv){

    fileptr = fopen(argv[1], "r");

    fileBuffer = filetobuffer(fileptr);

    char *Wbuffer = NULL;
    int start = 0;

    for (int i = 0; i <= FILE_SIZE; i++) {
        if (fileBuffer[i] == ' ' || fileBuffer[i] == ';' || fileBuffer[i] == '\n' || fileBuffer[i] == '\0') {
            if (i > start) {
                int wordLength = i - start;
                Wbuffer = (char *)malloc(wordLength + 1); // Allocate memory for the word
                
                if (Wbuffer == NULL) {
                    // Handle allocation failure
                    fprintf(stderr, "Memory allocation failed\n");
                    exit(1);
                }

                // Copy the characters from fileBuffer to Wbuffer
                for (int j = 0; j < wordLength; j++) {
                    Wbuffer[j] = fileBuffer[start + j];
                }
                Wbuffer[wordLength] = '\0';

                // TODO Write the tokenizer here
                

                free(Wbuffer); // Free the allocated memory
                Wbuffer = NULL; // Reset Wbuffer to NULL
            }
            start = i + 1;
        }
    }

}