#include "../../include/lexer/lexer.h"
#include "../../include/core/core.h"

#include "../../include/DS/list.h"
#include "../../include/DS/dict.h"

#include "../../include/token/tokendef.h"

#include <stdio.h>
#include <stdlib.h>

#define _EOL_CHAR ';'
#define _DOUBLE_START_QUOTE '"'
#define _DOUBLE_END_QUOTE '"'

char *Wbuffer = NULL;
char *lineBuffer = NULL;

int lineLength;

int isNum(char *word){
    char *nums = "0123456789";

    for(int i = 0; i < 10; i++){
        if(nums[i] == word[0]){
            return 1;
        }
    }

    return 0;
}

// Needs improvement
char *getStrings(char *word, int line_length){

}

int isString(char *word, int wordLength){
}

list *tokenize(list *head, char *fileBuffer){
    return head;
}

void freetokenlist(){
    free(Wbuffer);
    free(lineBuffer);
    freetokendeflist();
}