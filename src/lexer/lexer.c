#include "../../include/lexer/lexer.h"
#include "../../include/DS/list.h"
#include "../../include/DS/dict.h"

#include "../../include/token/tokendef.h"

#include <stdio.h>
#include <stdlib.h>


list *tokenize(list *head, char *buffer){
    // TODO check if the word is a int, string, variable

    if(_token_def_list == NULL){
        printf("Created the token list\n");
        addtoken();
    }

    //printf("%s", buffer);
    head = append(head, creatitem(getvaluefromkey(_token_def_list, buffer), buffer));

    return head;
}
