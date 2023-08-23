#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/core/core.h"

FILE *fileptr;
char *content;
long long length = -1;

int main(int argc, char **argv){

    fileptr = fopen(argv[1], "r");
    if(fileptr == NULL){
        printf("Error reading the file.\n");
        return 1;
    }

    while(!FILE_HAS_ENDED){
        if((content = getWord(fileptr)) == NULL) break;

        printf("%s", content);
        //break;
    }
    
    printf("\nDone.");
    return 0;
}