#include "../../include/core/core.h"
#include <stdio.h>
#include <stdlib.h>

// Used to store word as the it encounters them
// x = 1 + 2
// buffer will store it as {"x"}, {"1"}, {"2"}
char buffer[25];
char ch;
short int FILE_HAS_ENDED = 0;
short int i;

char *getWord(FILE *file){

    i = 0;
    while (!FILE_HAS_ENDED)
    {
        ch = fgetc(file);

        if(ch != ' ' && ch != -1) buffer[i] = ch;
        else return;

        i++;
    }
}