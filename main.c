#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fileptr;
char content = '\0';
long long length = -1;

char *buffer[25];

int main(int argc, char **argv){

    fileptr = fopen(argv[1], "r");

    if(fileptr == NULL){
        printf("Error reading the file.\n");
    }

    while(content != -1){
        length++;
        content = fgetc(fileptr);
    }

    printf("Length of the file is = %lld\n", length);

    fseek(fileptr, 0, 0);

    int i = 0;
    while(length){
        content = fgetc(fileptr);
        if(buffer[i] == ' ') break;
        buffer[i] = content;
        length--;
        i++;
    }
    
    printf("\n");

    fclose(fileptr);
    
    return 0;
}