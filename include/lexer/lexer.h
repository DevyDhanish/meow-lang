#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "../DS/list.h"

// @brief tokenizes word according to the tokes defined in /include/token/tokendef.h
// @param buffer containing a single `word` example {"return"}, {"1"} etc
// @returns a list of dict with key as the token and values as the actual suppiled word example {(key : __RETURN__, value : return)}
list *tokenize(list *head, char *buffer);

/*
@brief this actually frees the token list defied in the include/token/tokendef.h
becaues program gives error if I include both the lexer and tokedef in the meow.c file
*/
void freetokenlist();

#endif