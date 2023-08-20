#include <stdio.h>

char *buffer;
FILE *fileptr;
char content = '\0';

int main(int argc, char **argv){

    printf("%d\n", argc);

    fileptr = fopen(argv[1], "r");

    if(fileptr == NULL){
        printf("Error reading the file.\n");
    }

    while(content != -1){
        printf("%c", content);
        content = fgetc(fileptr);
    }

    printf("\n");
    
    return 0;
}