#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Datastructures
#include "../include/DS/list.h"
#include "../include/DS/dict.h"

// Libraries
#include "../include/core/core.h"
#include "../include/parser/parser.h"
#include "../include/lexer/lexer.h"
#include "../include/token/tokendef.h"

FILE *fileptr;
char *fileBuffer;
FILE *asmfile;


int main(int argc, char **argv){

    fileptr = fopen(argv[1], "r");

    if(fileptr == NULL){
        printf("\x1b[31mFatal\x1b[0m : No input files\n");
        return 1;
    }

    // Read the file and put it in buffer
    fileBuffer = filetobuffer(fileptr);

    // List to store the tokens
    list *token_list = NULL;
    //addtoken();

    // Get each word from the buffer
    // And tokenize it
    token_list = tokenize(token_list, fileBuffer);

    if(token_list == NULL){
        printf("\nFailed to tokenize the contents\n");
        return 1;
    }

    tree *ast = generateAST(token_list);

    displaydict(token_list);

    // free everthing
    // freefilebuffer();
    // freetokenlist();

    printf("Meow lang compiling \x1b[32mDone...\x1b[0m\n");
    
    return 0;
}