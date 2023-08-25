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

list *_token_def_list = NULL;


void addtoken(){
    _token_def_list = append(_token_def_list, creatitem((char *)"return", __RETURN__));

    _token_def_list = append(_token_def_list, creatitem((char *)"null", __NULL__));

    _token_def_list = append(_token_def_list, creatitem((char *)"var", __VAR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"=", __EQU__));

    _token_def_list = append(_token_def_list, creatitem((char *)"+", __PLUS__));

    _token_def_list = append(_token_def_list, creatitem((char *)"-", __MINUS__));
}

#endif