#include "../../include/token/tokendef.h"

#include "../../include/DS/dict.h"
#include "../../include/DS/list.h"
#include <string.h>
#include <stdlib.h>

/*
All the defined tokens
*/
char *__RETURN__ = "__RETURN__";
char *__NULL__ = "__NULL__";
char *__VAR__ = "__VAR__";
char *__EQU__ = "__EQU__";
char *__OPERATOR__ = "__OPERATOR__";
char *__INT__ = "__INT__";
char *__IMPORT__ = "__IMPORT__";
char *__IF__ = "__IF__";
char *__ELSE__ = "__ELSE__";
char *__ELSEIF__ = "__ELSEIF__";
char *__WHILE__ = "__WHILE__";
char *__PLUSEQU__ = "__PLUSEQU__";
char *__MINUSEQU__ = "__MINUSEQU__";
char *__STRING__ = "__STRING__";
char *__FUNC__ = "__FUNC__";
char *__MAIN__ = "__MAIN__";

list *_token_def_list = NULL;               // stores all the token with there respective value example {(key : __NULL__, value : null)}

/*
Adds all the defined tokens above to the `list *_token_def_list` variable as dict struct.
the key will the word the meow lang might have exaple return, fnc, null etc
the value will be the defined token for each word
*/
void addtoken(){
    _token_def_list = append(_token_def_list, creatitem((char *)"show", __RETURN__));

    _token_def_list = append(_token_def_list, creatitem((char *)"null", __NULL__));

    _token_def_list = append(_token_def_list, creatitem((char *)"var", __VAR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"=", __EQU__));

    _token_def_list = append(_token_def_list, creatitem((char *)"+", __OPERATOR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"/", __OPERATOR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"*", __OPERATOR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"%", __OPERATOR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"-", __OPERATOR__));

    _token_def_list = append(_token_def_list, creatitem((char *)"int", __INT__));

    _token_def_list = append(_token_def_list, creatitem((char *)"@add", __IMPORT__));

    _token_def_list = append(_token_def_list, creatitem((char *)"if", __IF__));

    _token_def_list = append(_token_def_list, creatitem((char *)"else", __ELSE__));

    _token_def_list = append(_token_def_list, creatitem((char *)"elif", __ELSEIF__));

    _token_def_list = append(_token_def_list, creatitem((char *)"while", __WHILE__));

    _token_def_list = append(_token_def_list, creatitem((char *)"+=", __PLUSEQU__));

    _token_def_list = append(_token_def_list, creatitem((char *)"-=", __MINUSEQU__));

    _token_def_list = append(_token_def_list, creatitem((char *)"str", __STRING__));

    _token_def_list = append(_token_def_list, creatitem((char *)"fnc", __FUNC__));
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