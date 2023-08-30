#ifndef TOKENDEF_H
#define TOKENDEF_H

#include "../DS/dict.h"
#include "../DS/list.h"
#include <string.h>
#include <stdlib.h>

/*
All the defined tokens
*/
extern char *__RETURN__;
extern char *__SHOW__;
extern char *__NULL__;
extern char *__VAR__;
extern char *__EQU__;
extern char *__OPERATOR__;
extern char *__INT__;
extern char *__IMPORT__;
extern char *__IF__;
extern char *__ELSE__;
extern char *__ELSEIF__;
extern char *__WHILE__;
extern char *__PLUSEQU__;
extern char *__MINUSEQU__;
extern char *__STRING__;
extern char *__FUNC__;
extern char *__MAIN__;

extern list *_token_def_list;               // stores all the token with there respective value example {(key : __NULL__, value : null)}

/*
Adds all the defined tokens above to the `list *_token_def_list` variable as dict struct.
the key will the word the meow lang might have exaple return, fnc, null etc
the value will be the defined token for each word
*/
void addtoken();

/*
checks if the provided word is a token or not
returns 1 if it is, return 0 if not and -1 it the variable `list *_token_def_list` has not been initiliazed and we call this function.
*/
int isToken(char *buffer);

/*
Frees the allocated space for the `list *_token_def_list` variable
*/
void freetokendeflist();

#endif // TOKENDEF_H