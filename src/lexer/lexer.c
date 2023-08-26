#include "../../include/lexer/lexer.h"
#include "../../include/DS/list.h"
#include "../../include/DS/dict.h"

#include "../../include/token/tokendef.h"

#include <stdio.h>
#include <stdlib.h>

int isNum(char *word){
    char *nums = "0123456789";

    for(int i = 0; i < 10; i++){
        if(nums[i] == word[0]){
            return 1;
        }
    }

    return 0;
}


list *tokenize(list *head, char *buffer){
    // TODO check if the word is a int, string, variable

    if(_token_def_list == NULL){
        //printf("Created the token list\n");
        addtoken();
    }

    if(isNum(buffer)){
        head = append(head, creatitem(getvaluefromkey(_token_def_list, (char *)"int"), buffer));
    }
    else if(!isToken(buffer)){
        head = append(head, creatitem(getvaluefromkey(_token_def_list, (char*)"var"), buffer));
    }
    else{
        head = append(head, creatitem(getvaluefromkey(_token_def_list, buffer), buffer));
    }

    return head;
}
