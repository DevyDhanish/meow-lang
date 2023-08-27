#ifndef TOKENDEF_H
#define TOKENDEF_H

#include "../DS/dict.h"
#include "../DS/list.h"
#include <string.h>
#include <stdlib.h>

/*
All the defined tokens
*/
char *__RETURN__ = "__RETURN__";
char *__NULL__ = "__NULL__";
char *__VAR__ = "__VAR__";
char *__EQU__ = "__EQU__";
char *__PLUS__ = "__PLUS__";
char *__MINUS__ = "__MINUS__";
char *__INT__ = "__INT__";

list *_token_def_list = NULL;               // stores all the token with there respective value example {(key : __NULL__, value : null)}

/*
Adds all the defined tokens above to the `list *_token_def_list` variable as dict struct.
the key will the word the meow lang might have exaple return, fnc, null etc
the value will be the defined token for each word
*/
void addtoken(){
    _token_def_list = append(_token_def_list, creatitem((char *)"return", __RETURN__));

    _token_def_list = append(_token_def_list, creatitem((char *)"null", __NULL__));

    _token_def_list = append(_token_def_list, creatitem((char *)"var", __VAR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"=", __EQU__));

    _token_def_list = append(_token_def_list, creatitem((char *)"+", __PLUS__));

    _token_def_list = append(_token_def_list, creatitem((char *)"-", __MINUS__));

    _token_def_list = append(_token_def_list, creatitem((char *)"int", __INT__));
}

/*
checks if the provided word is a token or not
returns 1 if it is, return 0 if not and -1 it the variable `list *_token_def_list` has not been initiliazed and we call this function.
*/
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

/*
Frees the allocated space for the `list *_token_def_list` variable
*/
void freetokendeflist(){

    while(_token_def_list->next != NULL){
        dict *item = (dict *) _token_def_list->data;

        free(item);

        list *temp = _token_def_list;

        _token_def_list = _token_def_list->next;

        free(temp);
    } 

}

/*
Checks if the first letter of the provided buffer is a number not not, variable in the meow lang should not start with a number else they will be considered as a number this migth break the compiling
return 1 if it is and 0 it not
*/
int isNum(char *word){
    char *nums = "0123456789";

    for(int i = 0; i < 10; i++){
        if(nums[i] == word[0]){
            return 1;
        }
    }

    return 0;
}

#endif