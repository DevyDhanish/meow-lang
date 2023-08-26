#ifndef TOKENDEF_H
#define TOKENDEF_H

#include "../DS/dict.h"
#include "../DS/list.h"
#include <string.h>

char *__RETURN__ = "__RETURN__";
char *__NULL__ = "__NULL__";
char *__VAR__ = "__VAR__";
char *__EQU__ = "__EQU__";
char *__PLUS__ = "__PLUS__";
char *__MINUS__ = "__MINUS__";
char *__INT__ = "__INT__";

list *_token_def_list = NULL;


void addtoken(){
    _token_def_list = append(_token_def_list, creatitem((char *)"return", __RETURN__));

    _token_def_list = append(_token_def_list, creatitem((char *)"null", __NULL__));

    _token_def_list = append(_token_def_list, creatitem((char *)"var", __VAR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"=", __EQU__));

    _token_def_list = append(_token_def_list, creatitem((char *)"+", __PLUS__));

    _token_def_list = append(_token_def_list, creatitem((char *)"-", __MINUS__));

    _token_def_list = append(_token_def_list, creatitem((char *)"int", __INT__));
}

int isToken(char *buffer){
    if(_token_def_list == NULL){
        printf("Token list is not initialized");
        return -1;
    }

    list *temp = _token_def_list;
    while(temp != NULL){
        dict *item = (dict *) temp->data;
        if(strcmp(item->key, buffer) == 0){
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}

#endif